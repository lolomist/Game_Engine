#version 450
#extension GL_ARB_separate_shader_objects : enable

#define MAX_LIGHTS 100

struct SpotLight {
    vec3 position;
    vec3  direction;
    float cutOff;
    float outerCutOff;

    vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct DirLight {
    vec3 direction;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {    
    vec3 position;
    
    float constant;
    float linear;
    float quadratic;  

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};  

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 cameraPos;
    vec3 objectColor;
    int spotLightCount;
    SpotLight spotLight[MAX_LIGHTS];
    DirLight dirLight;
    int pointLightsCount;
    PointLight pointLights[MAX_LIGHTS];
    Material material;
    int hasSpecularTexture;
} ubo;

layout(location = 0) in vec3 FragPosition;
layout(location = 1) in vec3 FragColor;
layout(location = 2) in vec2 FragTexCoord;
layout(location = 3) in vec3 FragNormal;

layout(location = 0) out vec4 outColor;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * ubo.material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * ubo.material.diffuse);
    vec3 specular = light.specular * (spec * ubo.material.specular);
    return (ambient + diffuse + specular) * ubo.objectColor;
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + 
  			     light.quadratic * (distance * distance));    
    // combine results
    vec3 ambient  = light.ambient  * ubo.material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * ubo.material.diffuse);
    vec3 specular = light.specular * (spec * ubo.material.specular);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular) * ubo.objectColor;
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.material.shininess);
    // attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    
    // spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    // combine results
    vec3 ambient  = light.ambient  * ubo.material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * ubo.material.diffuse);
    vec3 specular = light.specular * (spec * ubo.material.specular);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular) * ubo.objectColor;
}

void main() 
{
    // properties
    vec3 norm = normalize(FragNormal);
    vec3 viewDir = normalize(ubo.cameraPos - FragPosition);

    vec3 result = CalcDirLight(ubo.dirLight, norm, viewDir);

     for(int i = 0; i < ubo.pointLightsCount; i++)
        result += CalcPointLight(ubo.pointLights[i], norm, FragPosition, viewDir);    
    //phase 3: spot light
     for(int i = 0; i < ubo.spotLightCount; i++)
        result += CalcSpotLight(ubo.spotLight[i], norm, FragPosition, viewDir);   
    
    outColor = vec4(result , 1.0);
}

//void main() {
//    //vec3 lightColor = vec3(1.0, 0.5, 1.0);
//
//    //Ambient Light
//    vec3 ambient = ubo.light.ambient * ubo.material.ambient;
//
//    //Calculate diffuse impact
//    vec3 norm = normalize(FragNormal);
//    vec3 lightDir = normalize(ubo.light.pos - FragPosition); 
//    float diff = max(dot(norm, lightDir), 0.0);
//    vec3 diffuse = ubo.light.diffuse * (diff * ubo.material.diffuse);
//
//    //Calculate Specular Lighting
//    vec3 viewDir = normalize(ubo.cameraPos - FragPosition);
//    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.material.shininess);
//    vec3 specular = ubo.light.specular * (spec * ubo.material.specular);
//
//    vec3 result = (ambient + diffuse + specular) * FragColor;
//    outColor = vec4(result, 1.0);
//    
//    //outColor = texture(texSampler, vs_TexCoord) * (vec4(ambientLight, 1.f));
//
//    //Texture + color
//    //outColor = vec4(fragColor * texture(texSampler, fragTexCoord).rgb, 1.0);
//}
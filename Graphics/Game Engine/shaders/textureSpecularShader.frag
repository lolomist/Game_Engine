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
    float time;
} ubo;

layout(location = 0) in vec3 FragPosition;
layout(location = 1) in vec3 FragColor;
layout(location = 2) in vec2 FragTexCoord;
layout(location = 3) in vec3 FragNormal;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform sampler2D texSampler;
layout(binding = 2) uniform sampler2D texSpecular;
layout(binding = 3) uniform sampler2D texEmission;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir, vec3 textureMaterial, vec3 specularMaterial, vec3 emission)
{
    vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), ubo.material.shininess);
    // combine results
    vec3 ambient  = light.ambient  * textureMaterial;
    vec3 diffuse  = light.diffuse  * (diff * textureMaterial);
    vec3 specular = light.specular * (spec * specularMaterial);
    return (ambient + diffuse + specular);
}  

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 textureMaterial, vec3 specularMaterial, vec3 emission)
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
    vec3 ambient  = light.ambient  * textureMaterial;
    vec3 diffuse  = light.diffuse  * (diff * textureMaterial);
    vec3 specular = light.specular * (spec * specularMaterial);
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular + emission);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 textureMaterial, vec3 specularMaterial, vec3 emission)
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
    vec3 ambient = light.ambient * textureMaterial;
    vec3 diffuse = light.diffuse * (diff * textureMaterial);
    vec3 specular = light.specular * (spec * specularMaterial);
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;
    return (ambient + diffuse + specular + emission);
}

vec3 calculate_emission(vec3 specular, vec3 emission)
{
    vec3 show = step(vec3(1.0), vec3(1.0) - specular);
    return (emission * show) * mix( vec3( 1.0, 1.0, 0.0 ), vec3(texture(texEmission, FragTexCoord)).rgb, sin(ubo.time) * 1.0 );
}

void main()
{    
    // properties
    vec3 norm = normalize(FragNormal);
    vec3 viewDir = normalize(ubo.cameraPos - FragPosition);

    vec3 textureMaterial = vec3(texture(texSampler, FragTexCoord));
    vec3 specular = vec3(0.0, 0.0, 0.0);
    vec3 emission = vec3(0.0);
    if (ubo.hasSpecularTexture == 0) {
        specular = ubo.material.specular;
    }
    else if (ubo.hasSpecularTexture == 1) {
        specular = vec3(texture(texSpecular, FragTexCoord));
    }

    //Emission Texture loaded without specular, texSpecular = emission Texture
    else if (ubo.hasSpecularTexture == 2) {
        specular = ubo.material.specular;
        emission = vec3(texture(texSpecular, FragTexCoord));
    }

      //Emission Texture with specular
    else if (ubo.hasSpecularTexture == 3) {
        specular = vec3(texture(texSpecular, FragTexCoord));
        emission = calculate_emission(specular, vec3(texture(texEmission, FragTexCoord)).rgb);
        //emission = emission * sin(ubo.time) * 0.5 + 0.5) * 2.0;  
        //emission = emission  ;  
    }
    
    // phase 1: directional lighting
    vec3 result = CalcDirLight(ubo.dirLight, norm, viewDir, textureMaterial, specular, emission);
    // phase 2: point lights

    
   for(int i = 0; i < ubo.pointLightsCount; i++)
        result += CalcPointLight(ubo.pointLights[i], norm, FragPosition, viewDir,textureMaterial, specular, emission);    
    //phase 3: spot light

    for(int i = 0; i < ubo.spotLightCount; i++)
        result += CalcSpotLight(ubo.spotLight[i], norm, FragPosition, viewDir, textureMaterial,specular, emission);
    
    outColor = vec4(result, 1.0);
}

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

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

//layout(location = 4) in vec3 inLightPos0;

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec3 FragColor;
layout(location = 2) out vec2 FragTexCoord;
layout(location = 3) out vec3 FragNormal;
//layout(location = 4) out vec3 vs_lightPos0;
//layout(location = 5) out vec3 vs_lightColor;
//layout(location = 6) out vec3 vs_cameraPos;

void main() {
    //Send data to fragment Shader
    FragColor = ubo.objectColor;
    FragTexCoord = inTexCoord;
    
    //vs_lightPos0 = ubo.lightPos;
    //vs_lightColor = ubo.lightColor;
    //vs_cameraPos = ubo.cameraPos;

    gl_Position = ubo.proj * ubo.view * ubo.model * vec4(inPosition, 1.0);
    FragPosition = vec3(ubo.model * vec4(inPosition, 1.0));
    FragNormal = mat3(transpose(inverse(ubo.model))) * inNormal;
    //FragNormal = mat3(ubo.model) * inNormal;
}
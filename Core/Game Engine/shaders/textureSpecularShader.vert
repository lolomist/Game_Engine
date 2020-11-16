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

layout(location = 0) out vec3 vs_position;
layout(location = 1) out vec3 vs_color;
layout(location = 2) out vec2 vs_texCoord;
layout(location = 3) out vec3 vs_normal;


void main() {
    //Send data to fragment Shader
    vs_color = inColor;
    vs_texCoord = inTexCoord;

    gl_Position = ubo.proj * ubo.view * ubo.model  * vec4(inPosition, 1.0);
    vs_position = vec3(ubo.model * vec4(inPosition, 1.0));
    vs_normal = mat3(transpose(inverse(ubo.model))) * inNormal;
}
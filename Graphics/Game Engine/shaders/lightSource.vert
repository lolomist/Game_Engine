#version 450
#extension GL_ARB_separate_shader_objects : enable

struct Light {
    vec3 pos;

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

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
    vec3 cameraPos;
    vec3 objectColor;
    Light light;
    Material material;
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

void main() {
    //Send data to fragment Shader
    FragPosition = inPosition;
    FragColor = ubo.objectColor;
    FragTexCoord = inTexCoord;
    gl_Position = ubo.proj * ubo.view * ubo.model  * vec4(inPosition, 1.0);
    FragNormal = mat3(ubo.model) * inNormal;
}
#pragma once
#include <glm/glm.hpp>

const int MAX_LIGHTS = 100;

struct SptLight {
	alignas(16) glm::vec3 pos;
	alignas(16) glm::vec3 direction;
	alignas(4) float cutOff;
	alignas(4) float outerCutOff;

	alignas(16) glm::vec3 ambient;
	alignas(16) glm::vec3 diffuse;
	alignas(16) glm::vec3 specular;

	alignas(4) float constant;
	alignas(4) float linear;
	alignas(4) float quadratic;
};

struct DirLight {
	alignas(16) glm::vec3 direction;

	alignas(16) glm::vec3 ambient;
	alignas(16) glm::vec3 diffuse;
	alignas(16) glm::vec3 specular;
};

struct PtLight {
	alignas(16) glm::vec3 position;

	alignas(4) float constant;
	alignas(4) float linear;
	alignas(4) float quadratic;

	alignas(16) glm::vec3 ambient;
	alignas(16) glm::vec3 diffuse;
	alignas(16) glm::vec3 specular;
};

struct Material {
	alignas(16) glm::vec3 ambient;
	alignas(16) glm::vec3 diffuse;
	alignas(16) glm::vec3 specular;
	alignas(4) float shininess;
};

struct UniformBufferObject {
	alignas(16) glm::mat4 model;
	alignas(16) glm::mat4 view;
	alignas(16) glm::mat4 proj;
	alignas(16) glm::vec3 cameraPos;
	alignas(16) glm::vec3 objectColor;
	alignas(4) int spotLightCount;
	alignas(16) SptLight spotLight[MAX_LIGHTS];
	alignas(16) DirLight dirLight;
	alignas(4) int pointLightsCount;
	alignas(16) PtLight pointLights[MAX_LIGHTS];
	alignas(16) Material material;
	alignas(4) int hasSpecularTexture;
	alignas(4) float time;
};
#pragma once
#include <glm\glm.hpp>
#include "../Entity.h"
#include "../Utils.h"
#include "../Shaders_class/Shader.h"
#include <vulkan/vulkan.h>
#include "../UBO.h"
#include <vector>

class PointLight : public Entity
{
public:
	PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Shader *shader, Utils *utils);
	PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Entity *cube, Shader* shader, Utils *utils);
	

	// Light parameters
	float getConstant();
	float getLinear();
	float getQuadratic();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();

	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);

	std::vector<VkDeviceMemory> getLightBufferMemory();

	void bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index);

	virtual const glm::vec3 getPosition() const override;
	virtual glm::vec3 getRotation() override;
	virtual glm::vec3 getScale() override;
	virtual glm::vec3 getColor() override;
	virtual void setPosition(glm::vec3 position) override;
	virtual void setRotation(glm::vec3 rotation) override;
	virtual void setScale(glm::vec3 scale) override;
	virtual void setColor(glm::vec3 color) override;
	virtual void move(float speed, const int direction, float dt) override;
	virtual void rotate(const glm::vec3 rotation, float dt) override;
	virtual void link(Entity* entity) override;

private:
	Shader* _shader;
	Utils* _utils;
	glm::vec3 _position;

	float _constant;
	float _linear;
	float _quadratic;

	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;

	std::vector<VkBuffer> _pointLightBuffers;
	std::vector<VkDeviceMemory> _pointLightBuffersMemory;

	std::vector<VkDescriptorSet> _descriptorSets;

	Entity *_linkedEntity;
};


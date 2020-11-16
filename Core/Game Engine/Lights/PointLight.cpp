#include "PointLight.h"

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Shader* shader, Utils* utils)
{
	_utils = utils;
	_position = position;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_shader = shader;
}

PointLight::PointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Entity* cube, Shader* shader, Utils *utils)
{
	_utils = utils;
	_position = position;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_shader = shader;

	link(cube);
}

float PointLight::getConstant()
{
	return _constant;
}

float PointLight::getLinear()
{
	return _linear;
}

float PointLight::getQuadratic()
{
	return _quadratic;
}

glm::vec3 PointLight::getAmbient()
{
	return _ambient;
}

glm::vec3 PointLight::getDiffuse()
{
	return _diffuse;
}

glm::vec3 PointLight::getSpecular()
{
	return _specular;
}

void PointLight::setConstant(float constant)
{
	_constant = constant;
}

void PointLight::setLinear(float linear)
{
	_linear = linear;
}

void PointLight::setQuadratic(float quadratic)
{
	_quadratic = quadratic;
}

void PointLight::setAmbient(glm::vec3 ambient)
{
	_ambient = ambient;
}

void PointLight::setDiffuse(glm::vec3 diffuse)
{
	_diffuse = diffuse;
}

void PointLight::setSpecular(glm::vec3 specular)
{
	_specular = specular;
}


std::vector<VkDeviceMemory> PointLight::getLightBufferMemory()
{
	return _pointLightBuffersMemory;
}

void PointLight::bindCommandBuffer(VkCommandBuffer commandBuffer, size_t index)
{
	vkCmdBindDescriptorSets(commandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, _shader->getPipelineLayout(), 1, 1, &_descriptorSets[index], 0, nullptr);
}


const glm::vec3 PointLight::getPosition() const
{
	return _position;
}

glm::vec3 PointLight::getRotation()
{
	return glm::vec3();
}

glm::vec3 PointLight::getScale()
{
	return glm::vec3();
}

glm::vec3 PointLight::getColor()
{
	return glm::vec3();
}

void PointLight::setPosition(glm::vec3 position)
{
	_position = position;
}

void PointLight::setRotation(glm::vec3 rotation)
{
}

void PointLight::setScale(glm::vec3 scale)
{
}

void PointLight::setColor(glm::vec3 color)
{
}

void PointLight::move(float speed, const int direction, float dt)
{
	switch (direction) {
	case UP:
		_position = this->moveUp(_position, speed, dt, _linkedEntity);
		break;
	case DOWN:
		_position = this->moveDown(_position, speed, dt, _linkedEntity);
		break;
	case FORWARD:
		_position = this->moveForward(_position, speed, dt, _linkedEntity);
		break;
	case BACKWARD:
		_position = this->moveBackward(_position, speed, dt, _linkedEntity);
		break;
	case LEFT:
		_position = this->moveLeft(_position, speed, dt, _linkedEntity);
		break;
	case RIGHT:
		_position = this->moveRight(_position, speed, dt, _linkedEntity);
		break;
	}
}

void PointLight::rotate(const glm::vec3 rotation, float dt)
{
}

void PointLight::link(Entity* entity)
{
	_linkedEntity = entity;
}

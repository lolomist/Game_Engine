#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, 
	glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff)
{
	_position = position;
	_direction = direction;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_cutOff = cutOff;
	_outerCutOff = outerCutOff;
}

SpotLight::SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, float outerCutOff, Entity* cube)
{
	_position = position;
	_direction = direction;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_cutOff = cutOff;
	_outerCutOff = outerCutOff;

	link(cube);
}

glm::vec3 SpotLight::getDirection()
{
	return _direction;
}

glm::vec3 SpotLight::getAmbient()
{
	return _ambient;
}

glm::vec3 SpotLight::getDiffuse()
{
	return _diffuse;
}

glm::vec3 SpotLight::getSpecular()
{
	return _specular;
}

float SpotLight::getConstant()
{
	return _constant;
}

float SpotLight::getLinear()
{
	return _linear;
}

float SpotLight::getQuadratic()
{
	return _quadratic;
}

float SpotLight::getCutOff()
{
	return _cutOff;
}

float SpotLight::getOuterCutOff()
{
	return _outerCutOff;
}

void SpotLight::setDirection(glm::vec3 direction)
{
	_direction = direction;
}

void SpotLight::setAmbient(glm::vec3 ambient)
{
	_ambient = ambient;
}

void SpotLight::setDiffuse(glm::vec3 diffuse)
{
	_diffuse = diffuse;
}

void SpotLight::setSpecular(glm::vec3 specular)
{
	_specular = specular;
}

void SpotLight::setConstant(float constant)
{
	_constant = constant;
}

void SpotLight::setLinear(float linear)
{
	_linear = linear;
}

void SpotLight::setQuadratic(float quadratic)
{
	_quadratic = quadratic;
}

void SpotLight::setCutOff(float cutOff)
{
	_cutOff = cutOff;
}

void SpotLight::setOuterCutOff(float outerCutOff)
{
	_outerCutOff = outerCutOff;
}

const glm::vec3 SpotLight::getPosition() const
{
	return _position;
}

glm::vec3 SpotLight::getRotation()
{
	return glm::vec3();
}

glm::vec3 SpotLight::getScale()
{
	return glm::vec3();
}

glm::vec3 SpotLight::getColor()
{
	return _diffuse;
}

void SpotLight::setPosition(glm::vec3 position)
{
	_position = position;
}

void SpotLight::setRotation(glm::vec3 rotation)
{
}

void SpotLight::setScale(glm::vec3 scale)
{
}

void SpotLight::setColor(glm::vec3 color)
{
	setDiffuse(color);
	setSpecular(color);
}

void SpotLight::move(float speed, const int direction, float dt)
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

void SpotLight::rotate(const glm::vec3 rotation, float dt)
{
}

void SpotLight::link(Entity* entity)
{
	_linkedEntity = entity;
}

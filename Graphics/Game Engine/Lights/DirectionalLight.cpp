#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_direction = direction;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
}

glm::vec3 DirectionalLight::getDirection()
{
	return _direction;
}

glm::vec3 DirectionalLight::getAmbient()
{
	return _ambient;
}

glm::vec3 DirectionalLight::getDiffuse()
{
	return _diffuse;
}

glm::vec3 DirectionalLight::getSpecular()
{
	return _specular;
}

//const glm::vec3 DirectionalLight::getPosition() const
//{
//	return glm::vec3();
//}
//
//glm::vec3 DirectionalLight::getRotation()
//{
//	return glm::vec3();
//}
//
//glm::vec3 DirectionalLight::getScale()
//{
//	return glm::vec3();
//}
//
//glm::vec3 DirectionalLight::getColor()
//{
//	return glm::vec3();
//}
//
//void DirectionalLight::setPosition(glm::vec3 position)
//{
//}
//
//void DirectionalLight::setRotation(glm::vec3 rotation)
//{
//}
//
//void DirectionalLight::setScale(glm::vec3 scale)
//{
//}
//
//void DirectionalLight::setColor(glm::vec3 color)
//{
//}
//
//void DirectionalLight::move(float speed, const int direction, float dt)
//{
//}
//
//void DirectionalLight::rotate(const glm::vec3 rotation, float dt)
//{
//}
//
//void DirectionalLight::link(Entity* entity)
//{
//}

void DirectionalLight::setDirection(glm::vec3 direction)
{
	_direction = direction;
}

void DirectionalLight::setAmbient(glm::vec3 ambient)
{
	_ambient = ambient;
}

void DirectionalLight::setDiffuse(glm::vec3 diffuse)
{
	_diffuse = diffuse;
}

void DirectionalLight::setSpecular(glm::vec3 specular)
{
	_specular = specular;
}

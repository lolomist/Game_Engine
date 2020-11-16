#pragma once
#include <glm\glm.hpp>
#include "../Entity.h"

class SpotLight : public Entity
{
public:
	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, 
		float constant, float linear, float quadratic, float cutOff, float outerCutOff);

	SpotLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,
		float constant, float linear, float quadratic, float cutOff, float outerCutOff, Entity *cube);

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
	
	glm::vec3 getDirection();
	glm::vec3 getAmbient();
	glm::vec3 getDiffuse();
	glm::vec3 getSpecular();
	float getConstant();
	float getLinear();
	float getQuadratic();
	float getCutOff();
	float getOuterCutOff();

	void setDirection(glm::vec3 direction);
	void setAmbient(glm::vec3 ambient);
	void setDiffuse(glm::vec3 diffuse);
	void setSpecular(glm::vec3 specular);
	void setConstant(float constant);
	void setLinear(float linear);
	void setQuadratic(float quadratic);
	void setCutOff(float cutOff);
	void setOuterCutOff(float outerCutOff);

private:
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	float _constant;
	float _linear;
	float _quadratic;
	float _cutOff;
	float _outerCutOff;

	Entity* _linkedEntity;
};


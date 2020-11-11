#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm\ext\matrix_transform.hpp>

#include "enum.h"
#include "Entity.h"

class Camera : public Entity
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 direction);

	~Camera();

	const glm::mat4 getViewMatrix();

	const glm::vec3 getDirection() const;
	glm::vec3 getFront();

	void setFreeMovement(bool state);

	virtual void move(float speed, const int direction, float dt) override;
	virtual glm::vec3 moveForward(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;
	virtual glm::vec3 moveBackward(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;
	virtual glm::vec3 moveLeft(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;
	virtual glm::vec3 moveRight(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;
	//virtual glm::vec3 moveUp(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;
	//virtual glm::vec3 moveDown(glm::vec3 position, float speed, float dt, Entity* linkedEntity) override;

	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
	void updateInput(const float& dt, const double& offsetX, const double& offsetY);
	void setMousePos(double mouseX, double mouseY, float dt);

	virtual const glm::vec3 getPosition() const override;
	virtual glm::vec3 getRotation() override;
	virtual glm::vec3 getScale() override;
	virtual void setPosition(glm::vec3 position) override;
	virtual void setRotation(glm::vec3 rotation) override;
	virtual void setScale(glm::vec3 scale) override;
	virtual void rotate(const glm::vec3 rotation, float dt) override;
	virtual void link(Entity* entity) override;

private:
	glm::mat4 _viewMatrix;

	float _movementSpeed;
	float _sensitivity;

	glm::vec3 _worldUp;
	glm::vec3 _position;
	glm::vec3 _direction;
	glm::vec3 _front;
	glm::vec3 _right;
	glm::vec3 _up;

	float _pitch;
	float _yaw;
	float _roll;

	bool _freeMovement = false;

	bool _firstMouse = false;
	double _lastMouseX;
	double _lastMouseY;
	double _mouseOffsetX;
	double _mouseOffsetY;

	Entity* _linkedEntity;

	void updateCameraVectors();

	// Inherited via Entity
	

	// Inherited via Entity
	virtual glm::vec3 getColor() override;


	// Inherited via Entity
	virtual void setColor(glm::vec3 color) override;

};


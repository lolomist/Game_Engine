#pragma once

#include <iostream>

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <glm\ext\matrix_transform.hpp>

enum direction { FORWARD = 0, BACKWARD, LEFT, RIGHT };

class Camera
{
public:
	Camera();
	Camera(glm::vec3 position, glm::vec3 direction);

	~Camera();

	const glm::mat4 getViewMatrix();

	const glm::vec3 getPosition() const;
	const glm::vec3 getDirection() const;
	void setPosition(glm::vec3 position);

	void move(const float& dt, const int direction);
	void updateMouseInput(const float& dt, const double& offsetX, const double& offsetY);
	void updateInput(const float& dt, const double& offsetX, const double& offsetY);

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

	void updateCameraVectors();
};


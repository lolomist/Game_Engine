#include "Camera.h"

Camera::Camera()
{
	_viewMatrix = glm::mat4(1.f);

	_movementSpeed = 5.0f;
	_sensitivity = 5.0f;

	_worldUp = glm::vec3(glm::vec3(0.f, 1.f, 0.f));
	_direction = glm::vec3(0.f, 0.f, 90.f);
	_position = glm::vec3(0.f, 0.f, 0.0f);
	_right = glm::vec3(0.f);
	_up = _worldUp;

	_pitch = _direction.x;//50.f;
	_yaw = _direction.z;//-90.f;
	_roll = _direction.y;// 0.f;

	updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 direction)
{
	_viewMatrix = glm::mat4(1.f);

	_movementSpeed = 5.0f;
	_sensitivity = 5.0f;

	_worldUp = glm::vec3(glm::vec3(0.f, 1.f, 0.f));
	_direction = direction;
	_position = position;
	_right = glm::vec3(0.f);
	_up = _worldUp;

	_pitch = direction.x;//50.f;
	_yaw = direction.z;//-90.f;
	_roll = direction.y;// 0.f;

	updateCameraVectors();
}

Camera::~Camera()
{
}

const glm::mat4 Camera::getViewMatrix()
{
	updateCameraVectors();

	_viewMatrix = glm::lookAt(_position, _position + _front, _worldUp);

	return _viewMatrix;
}

const glm::vec3 Camera::getPosition() const
{
	return _position;
}

const glm::vec3 Camera::getDirection() const
{
	return _direction;
}

void Camera::setPosition(glm::vec3 position)
{
	_position = position;
}

void Camera::move(const float& dt, const int direction)
{
	//Update position
	switch (direction)
	{
	case FORWARD:
		_position += _front * _movementSpeed * dt;
		break;
	case BACKWARD:
		_position -= _front * _movementSpeed * dt;
		break;
	case LEFT:
		_position -= _right * _movementSpeed * dt;
		break;
	case RIGHT:
		_position += _right * _movementSpeed * dt;
		break;
	default:
		break;
	}
}

void Camera::updateMouseInput(const float& dt, const double& offsetX, const double& offsetY)
{
	//Update pitch yaw and roll
	_pitch += static_cast<float>(offsetY) * _sensitivity * dt;
	_yaw += static_cast<float>(offsetX) * _sensitivity * dt;

	if (_pitch > 80.f)
		_pitch = 80.f;
	else if (_pitch < -80.f)
		_pitch = -80.f;

	if (_yaw > 360.f || _yaw < -360.f) {
		_yaw = 0.f;
	}
}

void Camera::updateInput(const float& dt, const double& offsetX, const double& offsetY)
{
	updateMouseInput(dt, offsetX, offsetY);
}

// PRIVATE

void Camera::updateCameraVectors()
{
	_front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	_front.y = sin(glm::radians(_pitch));
	_front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	_front = glm::normalize(_front);
	_right = glm::normalize(glm::cross(_front, _worldUp));
	_up = glm::normalize(glm::cross(_right, _front));
}

#include "Camera.h"

Camera::Camera()
{
	_viewMatrix = glm::mat4(1.f);

	_movementSpeed = 5.0f;
	_sensitivity = 5.0f;

	_worldUp = glm::vec3(0.f, 1.f, 0.f);
	_direction = glm::vec3(0.f, 0.f, 90.f);
	_position = glm::vec3(0.f, 0.f, 0.0f);
	_right = glm::vec3(0.f);
	_up = _worldUp;

	_pitch = 50.f;
	_yaw = -90.f;
	_roll = 0.f;

	updateCameraVectors();
}

Camera::Camera(glm::vec3 position, glm::vec3 direction)
{
	_viewMatrix = glm::mat4(1.f);

	_movementSpeed = 5.0f;
	_sensitivity = 5.0f;

	_worldUp = glm::vec3(0.f, 1.f, 0.f);
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

const glm::vec3 Camera::getDirection() const
{
	return _direction;
}

glm::vec3 Camera::getFront()
{
	return _front;
}

void Camera::setFreeMovement(bool state)
{
	_freeMovement = true;
}

void Camera::setPosition(glm::vec3 position)
{
	_position = position;
}

void Camera::move(float speed, const int direction, float dt)
{
	//Update position
	switch (direction)
	{
	case UP:
		_position = moveUp(_position, speed, dt, _linkedEntity);
		break;
	case DOWN:
		_position = moveDown(_position, speed, dt, _linkedEntity);
		break;
	case FORWARD:
		moveForward(_position, speed, dt, _linkedEntity);
		break;
	case BACKWARD:
		moveBackward(_position, speed, dt, _linkedEntity);
		break;
	case LEFT:
		moveLeft(_position, speed, dt, _linkedEntity);
		break;
	case RIGHT:
		moveRight(_position, speed, dt, _linkedEntity);
		break;
	default:
		break;
	}
}

glm::vec3 Camera::moveForward(glm::vec3 position, float speed, float dt, Entity* linkedEntity)
{
	if (_freeMovement)
		_position += _front * speed * dt;
	else
		_position += glm::vec3(0.f, 0.f, 1.f) * speed * dt;
	
	if (linkedEntity) {
		linkedEntity->move(speed, FORWARD, dt);
	}
	return _position;
}

glm::vec3 Camera::moveBackward(glm::vec3 position, float speed, float dt, Entity* linkedEntity)
{
	if (_freeMovement)
		_position -= _front * speed * dt;
	else
		_position -= glm::vec3(0.f, 0.f, 1.f) * speed * dt;
	
	if (linkedEntity) {
		linkedEntity->move(speed, BACKWARD, dt);
	}
	return _position;
}

glm::vec3 Camera::moveLeft(glm::vec3 position, float speed, float dt, Entity* linkedEntity)
{
	if (_freeMovement)
		_position -= _right * speed * dt;
	else
		_position += glm::vec3(1.f, 0.f, 0.f) * speed * dt;
	
	if (linkedEntity) {
		linkedEntity->move(speed, LEFT, dt);
	}
	return _position;
}

glm::vec3 Camera::moveRight(glm::vec3 position, float speed, float dt, Entity* linkedEntity)
{
	if (_freeMovement)
		_position += _right * speed * dt;
	else
		_position -= glm::vec3(1.f, 0.f, 0.f) * speed * dt;

	if (linkedEntity) {
		linkedEntity->move(speed, RIGHT, dt);
	}
	return _position;
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

void Camera::setMousePos(double mouseX, double mouseY, float dt)
{
	double mouseOffsetX;
	double mouseOffsetY;

	if (this->_firstMouse)
	    {
	        this->_lastMouseX = mouseX;
	        this->_lastMouseY = mouseY;
	        this->_firstMouse = false;
	    }

	    //Calc offset
	    mouseOffsetX = mouseX - this->_lastMouseX;
	    mouseOffsetY = this->_lastMouseY - mouseY;

	    //Set last X and Y
	    this->_lastMouseX = mouseX;
	    this->_lastMouseY = mouseY;

		updateInput(dt, mouseOffsetX, mouseOffsetY);
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

glm::vec3 Camera::getColor()
{
	return glm::vec3();
}

void Camera::setColor(glm::vec3 color)
{
}

const glm::vec3 Camera::getPosition() const
{
	return _position;
}

glm::vec3 Camera::getRotation()
{
	return glm::vec3();
}

glm::vec3 Camera::getScale()
{
	return glm::vec3();
}

void Camera::setRotation(glm::vec3 rotation)
{
}

void Camera::setScale(glm::vec3 scale)
{
}

void Camera::rotate(const glm::vec3 rotation, float dt)
{
}

void Camera::link(Entity* entity)
{
	_linkedEntity = entity;
}

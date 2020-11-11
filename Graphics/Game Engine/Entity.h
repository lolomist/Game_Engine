#pragma once
#include <glm/glm.hpp>
#include "enum.h"

class Entity 
{
public:
	//virtual glm::vec3 getInitialPosition() = 0;
	virtual const glm::vec3 getPosition() const = 0;
	virtual glm::vec3 getRotation() = 0;
	virtual glm::vec3 getScale() = 0;
	virtual glm::vec3 getColor() = 0;

	virtual void setPosition(glm::vec3 position) = 0;
	virtual void setRotation(glm::vec3 rotation) = 0;
	virtual void setScale(glm::vec3 scale) = 0;
	virtual void setColor(glm::vec3 color) = 0;

	virtual void move(float speed, const int direction, float dt) = 0;
	virtual void rotate(const glm::vec3 rotation, float dt) = 0;

	virtual void link(Entity* entity) = 0;

	virtual glm::vec3 moveUp(glm::vec3 position, float speed, float dt, Entity* linkedEntity) {
		position += glm::vec3(0.f, 1.f, 0.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, UP, dt);
		}
		return position;
	}

	virtual glm::vec3 moveDown(glm::vec3 position, float speed, float dt, Entity* linkedEntity) {
		position -= glm::vec3(0.f, 1.f, 0.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, DOWN, dt);
		}
		return position;
	}

	virtual glm::vec3 moveForward(glm::vec3 position, float speed, float dt, Entity *linkedEntity) {
		position += glm::vec3(0.f, 0.f, 1.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, FORWARD, dt);
		}
		return position;
	}

	virtual glm::vec3 moveBackward(glm::vec3 position, float speed, float dt, Entity* linkedEntity) {
		position -= glm::vec3(0.f, 0.f, 1.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, BACKWARD, dt);
		}
		return position;
	}

	virtual glm::vec3 moveLeft(glm::vec3 position, float speed, float dt, Entity* linkedEntity) {
		position += glm::vec3(1.f, 0.f, 0.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, LEFT, dt);
		}
		return position;
	}

	virtual glm::vec3 moveRight(glm::vec3 position, float speed, float dt, Entity* linkedEntity) {
		position -= glm::vec3(1.f, 0.f, 0.f) * speed * dt;
		if (linkedEntity) {
			linkedEntity->move(speed, RIGHT, dt);
		}
		return position;
	}

	/*virtual glm::vec3 moveForward(glm::vec3 position) {

	}*/
};
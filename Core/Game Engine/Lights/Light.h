//#pragma once
//#include "../Entity.h"
//
//class Light : public Entity
//{
//public:
//	Light();
//	Light(glm::vec3 position, glm::vec3 color);
//	Light(glm::vec3 position, glm::vec3 color, Entity *cube);
//
//	virtual const glm::vec3 getPosition() const override;
//	virtual glm::vec3 getColor() override;
//	virtual glm::vec3 getRotation() override;
//	virtual glm::vec3 getScale() override;
//
//	virtual void setPosition(glm::vec3 position) override;
//	virtual void setRotation(glm::vec3 rotation) override;
//	virtual void setScale(glm::vec3 scale) override;
//	virtual void setColor(glm::vec3 color) override;
//
//	virtual void move(float speed, const int direction, float dt) override;
//	virtual void rotate(const glm::vec3 rotation, float dt) override;
//
//	virtual void link(Entity* entity) override;
//private:
//	glm::vec3 _position;
//	glm::vec3 _color;
//
//	Entity* _linkedEntity;
//
//	bool _showLight = false;
//};
//

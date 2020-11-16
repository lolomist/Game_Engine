//#include "Light.h"
//#include "../enum.h"
//
//Light::Light()
//{
//    _position = glm::vec3(0.f, 5.f, 0.f);
//    _color = glm::vec3(1.f);
//}
//
//Light::Light(glm::vec3 position, glm::vec3 color)
//{
//    _position = position;
//    _color = color;
//}
//
//Light::Light(glm::vec3 position, glm::vec3 color, Entity *cube)
//{
//    _showLight = true;
//    _position = position;
//    _color = color;
//
//    link(cube);
//}
//
//const glm::vec3 Light::getPosition() const
//{
//    return _position;
//}
//
//glm::vec3 Light::getColor()
//{
//    return _color;
//}
//
//glm::vec3 Light::getRotation()
//{
//    return glm::vec3();
//}
//
//glm::vec3 Light::getScale()
//{
//    return glm::vec3();
//}
//
//void Light::setPosition(glm::vec3 position)
//{
//    _position = position;
//}
//
//void Light::setRotation(glm::vec3 rotation)
//{
//}
//
//void Light::setScale(glm::vec3 scale)
//{
//}
//
//void Light::setColor(glm::vec3 color)
//{
//    _color = color;
//    _linkedEntity->setColor(color);
//}
//
//void Light::move(float speed, const int direction, float dt)
//{
//    switch (direction) {
//    case UP:
//        _position = this->moveUp(_position, speed, dt, _linkedEntity);
//        break;
//    case DOWN:
//        _position = this->moveDown(_position, speed, dt, _linkedEntity);
//        break;
//    case FORWARD:
//        _position = this->moveForward(_position, speed, dt, _linkedEntity);
//        break;
//    case BACKWARD:
//        _position = this->moveBackward(_position, speed, dt, _linkedEntity);
//        break;
//    case LEFT:
//        _position = this->moveLeft(_position, speed, dt, _linkedEntity);
//        break;
//    case RIGHT:
//        _position = this->moveRight(_position, speed, dt, _linkedEntity);
//        break;
//    }
//}
//
//void Light::rotate(const glm::vec3 rotation, float dt)
//{
//}
//
//void Light::link(Entity* entity)
//{
//    _linkedEntity = entity;
//}


#include "EntityManager/Entities/acrylic_entities.hpp"

template<typename T, typename R>
void A2D::EntityManager::PhysicsObject<T,R>::applyPhysics(){
    double xV = movementData.xAcceleration;
    double yV = movementData.yAcceleration;
    double xA = movementData.xAcceleration;
    double yA = movementData.yAcceleration;
    double x = xPosition;
    double y = yPosition;

    xV += xA;
    yV += yA;
    x += xV;
    y += yV;

    movementData.xAcceleration = xV;
    movementData.yAcceleration = yV;
    movementData.xAcceleration = xA;
    movementData.yAcceleration = yA;
    xPosition = x;
    yPosition = y;

}
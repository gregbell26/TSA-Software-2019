#ifndef ACRYLIC_ENTITIES_HPP
#define ACRYLIC_ENTITIES_HPP

#include <functional>

namespace A2D::EntityManager {

    class Entity{
        public:


        protected:
        ///texture stuff

        unsigned long entityID;
        double xPosition;
        double yPosition;
    };

    template<typename T, typename R>
    class UpdatableEntity {
    public:
        UpdatableEntity() = default;
        T onUpdate() { m_onUpdate(); }

        virtual ~UpdatableEntity() = default;

    protected:
        std::function<R> m_onUpdate;

    };


    struct Hit_Box{
        double xSize;
        double ySize;
        double xPos;
        double yPos;
    };

    class InteractableEntity{
        public:


        protected:
        Hit_Box hitBox;


    };

    struct Movement_Data{
        double xVelocity;
        double yVelocity;
        double xAcceleration;
        double yAcceleration;
    };

    class PhysicsObject{
        public:

        void applyPhysics(){
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

        protected:
        Movement_Data movementData;
    };

}

#endif //ACRYLIC_ENTITIES_HPP
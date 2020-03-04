#ifndef ACRYLIC_ENTITIES_HPP
#define ACRYLIC_ENTITIES_HPP

#include <functional>

namespace A2D::EntityManager {

    class Entity{
        public:
        

        protected:
        ///texture stuff

        int xPosition;
        int yPosition;
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
        int xSize;
        int ySize;
        int xPos;
        int yPos;
    };

    class InteractableEntity{
        public:


        protected:
        Hit_Box hitBox;


    };

    struct Movement_Data{
        int xVelocity;
        int yVelocity;
        int xAcceleration;
        int yAcceleration;
    };

    class PhysicsObject{
        public:

        protected:
        Movement_Data movementData;
    };

}


#endif //ACRYLIC_ENTITIES_HPP
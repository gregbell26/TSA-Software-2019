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
    class UpdatableEntity: public Entity {
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

    template<typename T, typename R>
    class InteractableEntity: public UpdatableEntity<T,R>{
        public:
        unsigned long* getCollidingEntities();
        bool isColliding(unsigned long);

        protected:
        Hit_Box hitBox;


    };

    struct Movement_Data{
        double xVelocity;
        double yVelocity;
        double xAcceleration;
        double yAcceleration;
    };

    template<typename T, typename R>
    class PhysicsObject: public InteractableEntity<T,R>{
        public:

        void applyPhysics();

        protected:
        Movement_Data movementData;
    };

}

#endif //ACRYLIC_ENTITIES_HPP

#include <vector>
#include "EntityManager/Entities/acrylic_entities.hpp"

template<typename T, typename R>
unsigned long* A2D::EntityManager::InteractableEntity<T,R>::getCollidingEntities(){
    std::vector<unsigned long>  collidingEntities;
    //
    return collidingEntities.data();
}

template<typename T, typename R>
bool A2D::EntityManager::InteractableEntity<T,R>::isColliding(unsigned long eid){
    bool colliding;

    return colliding;
}

unsigned long* getCollidingEntities(unsigned long eid){
    std::vector<unsigned long>  collidingEntities;
    //
    return collidingEntities.data();
}

bool isColliding(unsigned long eid1, unsigned long eid2){
    bool colliding;
    //
    return colliding;
}


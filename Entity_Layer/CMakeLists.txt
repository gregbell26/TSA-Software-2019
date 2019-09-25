cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

set(ENTITY_LAYER_SRC Entity.cpp)
set(ENTITY_LAYER_HEADER Entity.h InteractableEntity.h nonInteractableEntity.h)
set(ENTITY_LAYER ${ENTITY_LAYER_SRC} ${ENTITY_LAYER_HEADER})

add_library(AcrylicEntityLayer STATIC ${ENTITY_LAYER})
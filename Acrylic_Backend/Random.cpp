//
// Created by coolh on 1/8/2020.
//

#include "Random.h"
static glm::vec3 ranRGB()
{
    return glm::vec3(std::rand()%257, std::rand()%257, std::rand()%257);
}
    static glm::vec3 ranHSV()
    {
        return glm::vec3(std::rand()%360, std::rand()%100, std::rand()%100);
    }




//
// Created by gregb on 9/22/2019.
//

#ifndef QUEUEFAMILIES_HPP
#define QUEUEFAMILIES_HPP

#include <optional>
#include <vector>

//Queue Family stuff
struct QueueFamilyIndices {
    uint32_t graphicsFamily;

};

QueueFamilyIndices findQueueFamilies(VkPhysicalDevice physicalDevice){
    QueueFamilyIndices indices;
    uint32_t queueFamilyCount = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);



    return  indices;
}


#endif //QUEUEFAMILIES_HPP

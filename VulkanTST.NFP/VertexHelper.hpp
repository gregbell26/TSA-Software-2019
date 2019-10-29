#ifndef VERTEXHELPER_HPP
#define VERTEXHELPER_HPP

#include <glm/glm.hpp>
#include <array>

struct Vertex{
    glm::vec2 position;
    glm::vec3 color;

    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription = {};
        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(Vertex);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
        return bindingDescription;
    }

    static std::array<VkVertexInputAttributeDescription, 2 > getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions = {};//One index for each layout location in the shaders. Might wanna find way to do this dynamically
        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; //2 32bit floats - vec2
        attributeDescriptions[0].offset = offsetof(Vertex, position);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;//3 32bit floats - vec3
        attributeDescriptions[1].offset = offsetof(Vertex, color);

        return attributeDescriptions;
    }
};

const std::vector<Vertex> verties = {
        {{-1.0f, -1.0f}, {1.0f, 0.0f, 0.0f}},
        {{1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}},
        {{-1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}
};

#endif //VERTEXHELPER_HPP

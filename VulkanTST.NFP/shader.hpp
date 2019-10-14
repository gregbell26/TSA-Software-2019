//
// Created by Gregory Bell on 10/9/19.
//

#ifndef SHADER_HPP
#define SHADER_HPP

VkShaderModule createShaderModule (const std::vector<char>& shaderCode, VkDevice device){
    VkShaderModule shaderModule;

    VkShaderModuleCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = shaderCode.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(shaderCode.data());

    if(vkCreateShaderModule(device, &createInfo, nullptr, &shaderModule) != VK_SUCCESS){
        throw std::runtime_error("Failed to create shader module");
    }

    return shaderModule;
}


#endif //SHADER_HPP

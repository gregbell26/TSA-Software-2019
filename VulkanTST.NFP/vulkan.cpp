//Test file for vulkan
//This code is not for production
#include "vulkan.h"
#include "QueueFamilies.hpp"
#include "SwapChain.hpp"
#include "Shader.hpp"
#include "VertexHelper.hpp"
//Validation Layer Debug Bus

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
        void* pUserData){

    if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
        std::cerr << "Validation Layer: " << pCallbackData->pMessage << std::endl;
    }


    return VK_FALSE;
}

VkResult CreateDebugUtilsMessengerEXT(
        VkInstance vkInstance,
        const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
        const VkAllocationCallbacks* pAllocator,
        VkDebugUtilsMessengerEXT* pDebugMessenger){
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vkInstance, "vkCreateDebugUtilsMessengerEXT");
    if(func != nullptr){
        return func(vkInstance, pCreateInfo, pAllocator, pDebugMessenger);
    }
    else{
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

}

void DestroyDebugUtilsMessengerEXT(
        VkInstance vkInstance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator){
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(vkInstance, "vkDestroyDebugUtilsMessengerEXT");
    if(func != nullptr){
        func(vkInstance, debugMessenger, pAllocator);
    }

}

static void frameBufferResizeCallBack(GLFWwindow* glfwWindow, int width, int height){
    auto vulkanInstance = reinterpret_cast<Vulkan*>(glfwGetWindowUserPointer(glfwWindow));
    vulkanInstance->frameBufferResized = true;
}

void Vulkan::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();
}

void Vulkan::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    GLFWmonitor *primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode *videoMode = glfwGetVideoMode(primaryMonitor);
    std::cout << "MONITOR FOUND\n\tResolution: " << videoMode->width << "x" << videoMode->height << " @ " << videoMode->refreshRate << " hertz\n\tName: "
        <<glfwGetMonitorName(primaryMonitor) << std::endl;

    glfwWindow = glfwCreateWindow(videoMode->width, videoMode->height, "Vulkan", primaryMonitor, nullptr);

    glfwSetWindowUserPointer(glfwWindow, this);
    glfwSetFramebufferSizeCallback(glfwWindow, frameBufferResizeCallBack);

}

void Vulkan::initVulkan() {
    createInstance();
    setUpDebugBus();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandPool();
    createVertexBuffer();
    createIndexBuffer();
    createCommandBuffers();
    createSyncObjects();
}

void Vulkan::createInstance() {
    if(enableValidationLayers && !checkValidationLayerSupport())
        throw std::runtime_error("Validation layer requested but unsupported");

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "VulkanTST";
    appInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;


    auto extensions = getRequiredExtensions();
    createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
    createInfo.ppEnabledExtensionNames = extensions.data();

    if(enableValidationLayers){
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else
        createInfo.enabledLayerCount = 0;

    if(vkCreateInstance(&createInfo, nullptr, &vkInstance) != VK_SUCCESS)
        throw std::runtime_error("Failed to create Vulkan instance");

//    getSupportedExtensions();
}

bool Vulkan::checkValidationLayerSupport() {
    uint32_t layerCount;
    vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

    std::vector<VkLayerProperties> availableLayers(layerCount);
    vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

    for (const char* layerName : validationLayers) {
        bool layerFound = false;

        for (const auto& layerProperties : availableLayers) {
            if (strcmp(layerName, layerProperties.layerName) == 0) {
                layerFound = true;
                break;
            }
        }

        if (!layerFound) {
            return false;
        }
    }

    return true;
}

void Vulkan::getSupportedExtensions() {
    uint32_t extensionCount = 0;
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

    std::vector<VkExtensionProperties> extensions(extensionCount);
    vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, extensions.data());

    std::cout <<extensionCount << " Available Extensions" << std::endl;
    for(const auto& extension : extensions) {
        std::cout << "\t" << extension.extensionName << std::endl;
    }
}

std::vector<const char *> Vulkan::getRequiredExtensions() {
    uint32_t glfwExtensionsCount = 0;
    const char** glfwExtensions;

    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

    std::vector<const char*> extensions(glfwExtensions, glfwExtensions+glfwExtensionsCount);

    if(enableValidationLayers){
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    return extensions;
}

void Vulkan::setUpDebugBus() {
    if(!enableValidationLayers)
        return;
    VkDebugUtilsMessengerCreateInfoEXT createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
    createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
    createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
    createInfo.pfnUserCallback = debugCallback;

    if(CreateDebugUtilsMessengerEXT(vkInstance, &createInfo, nullptr, &debugBus) != VK_SUCCESS){
        throw std::runtime_error("Failed to create debug bus");
    }

}

void Vulkan::createSurface() {
    if(glfwCreateWindowSurface(vkInstance, glfwWindow, nullptr, &vkSurface) != VK_SUCCESS){
        throw std::runtime_error("FAILED TO CREATE WINDOW SURFACE");
    }
}

void Vulkan::pickPhysicalDevice() {
    uint32_t physicalDeviceCount = 0;
    vkEnumeratePhysicalDevices(vkInstance, &physicalDeviceCount, nullptr);

    if(physicalDeviceCount == 0){
        throw std::runtime_error("Failed to locate device with Vulkan support.");
    }

    std::vector<VkPhysicalDevice> physicalDevices(physicalDeviceCount);
    vkEnumeratePhysicalDevices(vkInstance, &physicalDeviceCount, physicalDevices.data());

    for(const auto device : physicalDevices){
        if(isPhysicalDeviceSuitable(device)){
            vkPhysicalDevice = device;
            break;
        }
    }

    if(vkPhysicalDevice == VK_NULL_HANDLE){
        throw std::runtime_error("Failed to locate suitable GPU for Vulkan");
    }

}

bool Vulkan::isPhysicalDeviceSuitable(VkPhysicalDevice physicalDevice) {
    bool extensionsSupported;
    bool swapChainAdequate;

    QueueFamilyIndices indices = findQueueFamilies(physicalDevice, vkSurface);

    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;

    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);
    extensionsSupported = checkDeviceExtensionSupport(physicalDevice);
    if(extensionsSupported){
        SwapChainSupportDetails swapChainSupport = querySwapChainSupport(physicalDevice, vkSurface);
        swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
    }

    //DEBUG MESSAGES
    if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU){
        std::cout << "Integrated GPU found. \n\tNOTE: Performance might be poor if this is the only GPU available on your system" << std::endl;
    }

    else if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
        std::cout << "Dedicated GPU found" << std::endl;
    }

    if(!extensionsSupported){
        std::cout << "GPU does NOT support required Vulkan Extensions" << std::endl;
    }
    if(!indices.isComplete()){
        std::cout << "GPU does NOT support Vulkan commands" << std::endl;
    }


    return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool Vulkan::checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice) {
    uint32_t extensionCount;
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);
    std::vector<VkExtensionProperties> availableExtensions(extensionCount);
    vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

    std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

    //tick off the extensions
    for (const auto &extension : availableExtensions){
        requiredExtensions.erase(extension.extensionName);
    }



    return requiredExtensions.empty();
}

void Vulkan::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(vkPhysicalDevice, vkSurface);

    std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
    std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};
    float queuePriority = 1.0f;

    for(uint32_t queueFamily : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo = {};
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = queueFamily;
        queueCreateInfo.queueCount = 1;//We break as soon as we find a valid queue
        queueCreateInfo.pQueuePriorities = &queuePriority;//Floats take up a lot of space so we want to pass by reference
        queueCreateInfos.push_back(queueCreateInfo);
    }
    VkPhysicalDeviceFeatures physicalDeviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
    createInfo.pQueueCreateInfos = queueCreateInfos.data();
    createInfo.pEnabledFeatures = &physicalDeviceFeatures;
    createInfo.enabledExtensionCount = static_cast<uint32_t >(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if(enableValidationLayers){
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();
    }
    else {
        createInfo.enabledLayerCount = 0;
    }

    if(vkCreateDevice(vkPhysicalDevice, &createInfo, nullptr, &vkDevice) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan device");
    }

    vkGetDeviceQueue(vkDevice, indices.graphicsFamily.value(), 0, &vkGraphicsQueue);
    vkGetDeviceQueue(vkDevice, indices.presentFamily.value(), 0, &vkPresentQueue);


}


void Vulkan::createSwapChain() {
    SwapChainSupportDetails swapChainSupport = querySwapChainSupport(vkPhysicalDevice, vkSurface);

    VkSurfaceFormatKHR surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
    VkPresentModeKHR presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
    VkExtent2D extent = chooseSwapExtent(swapChainSupport.surfaceCapabilities, glfwWindow);

    uint32_t imageCount = swapChainSupport.surfaceCapabilities.minImageCount + 1;
    if(swapChainSupport.surfaceCapabilities.maxImageCount > 0 && imageCount > swapChainSupport.surfaceCapabilities.maxImageCount){
        imageCount = swapChainSupport.surfaceCapabilities.maxImageCount;
    }

    VkSwapchainCreateInfoKHR createInfo = {};

    createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
    createInfo.surface = vkSurface;
    createInfo.minImageCount = imageCount;
    createInfo.imageFormat = surfaceFormat.format;
    createInfo.imageColorSpace = surfaceFormat.colorSpace;
    createInfo.imageExtent = extent;
    createInfo.imageArrayLayers = 1;
    createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

    QueueFamilyIndices indices = findQueueFamilies(vkPhysicalDevice, vkSurface);
    uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

    if(indices.graphicsFamily != indices.presentFamily){
        createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
        createInfo.queueFamilyIndexCount = 2;
        createInfo.pQueueFamilyIndices = queueFamilyIndices;
    } else {
        createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        createInfo.queueFamilyIndexCount = 0;
        createInfo.pQueueFamilyIndices = nullptr;
    }

    createInfo.preTransform = swapChainSupport.surfaceCapabilities.currentTransform;
    createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
    createInfo.presentMode = presentMode;
    createInfo.clipped = VK_TRUE;
    createInfo.oldSwapchain = VK_NULL_HANDLE;
    //Logical device not physical
    if(vkCreateSwapchainKHR(vkDevice, &createInfo, nullptr, &vkSwapChain) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan SwapChain");
    }

    vkGetSwapchainImagesKHR(vkDevice, vkSwapChain, &imageCount, nullptr);
    swapChainImages.resize(imageCount);
    vkGetSwapchainImagesKHR(vkDevice, vkSwapChain, &imageCount, swapChainImages.data());

    swapChainImageFormat = surfaceFormat.format;
    swapChainExtent = extent;
}

void Vulkan::createImageViews() {
    swapChainImageViews.resize(swapChainImages.size());

    VkImageViewCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
    createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
    createInfo.format = swapChainImageFormat;
    createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;
    createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    createInfo.subresourceRange.baseMipLevel = 0;
    createInfo.subresourceRange.levelCount = 1;
    createInfo.subresourceRange.baseArrayLayer = 0;
    createInfo.subresourceRange.layerCount = 1;

    for(size_t i = 0; i < swapChainImageViews.size(); i++){
        createInfo.image = VK_NULL_HANDLE;
        createInfo.image = swapChainImages[i];

        if(vkCreateImageView(vkDevice, &createInfo, nullptr, &swapChainImageViews[i]) != VK_SUCCESS){
            throw std::runtime_error("Failed to create Vulkan image views");
        }
    }

}

void Vulkan::createRenderPass() {
    VkAttachmentDescription colorAttachment = {};
    colorAttachment.format = swapChainImageFormat;
    colorAttachment.samples = VK_SAMPLE_COUNT_1_BIT;
    colorAttachment.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR;
    colorAttachment.storeOp = VK_ATTACHMENT_STORE_OP_STORE;
    colorAttachment.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
    colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
    colorAttachment.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
    colorAttachment.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR;

    VkAttachmentReference colorAttachmentRef = {};
    colorAttachmentRef.attachment = 0;
    colorAttachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

    VkSubpassDescription subpass = {};
    subpass.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
    subpass.colorAttachmentCount = 1;
    subpass.pColorAttachments = &colorAttachmentRef;

    VkSubpassDependency subpassDependency = {};
    subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
    subpassDependency.dstSubpass = 0;
    subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;//Wait for the image to be colored before we render
    subpassDependency.srcAccessMask = 0;
    subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
    subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;


    VkRenderPassCreateInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassInfo.attachmentCount = 1;
    renderPassInfo.pAttachments = &colorAttachment;
    renderPassInfo.subpassCount = 1;
    renderPassInfo.pSubpasses = &subpass;
    renderPassInfo.dependencyCount = 1;
    renderPassInfo.pDependencies = &subpassDependency;

    if(vkCreateRenderPass(vkDevice, &renderPassInfo, nullptr, &vkRenderPass) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan Render Pass");
    }

}

void Vulkan::createGraphicsPipeline() {
    auto vertShaderCode = readFile("shaders/vert.spv");
    auto fragShaderCode = readFile("shaders/frag.spv");

    auto bindingDes = Vertex::getBindingDescription();
    auto attribDes = Vertex::getAttributeDescriptions();

    VkShaderModule vertShaderModule = createShaderModule(vertShaderCode, vkDevice);
    VkShaderModule fragShaderModule = createShaderModule(fragShaderCode, vkDevice);

    VkPipelineShaderStageCreateInfo vertShaderStageCreateInfo = {};
    vertShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    vertShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    vertShaderStageCreateInfo.module = vertShaderModule;
    vertShaderStageCreateInfo.pName = "main";//the func name in the shader

    VkPipelineShaderStageCreateInfo fragShaderStageCreateInfo = {};
    fragShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    fragShaderStageCreateInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
    fragShaderStageCreateInfo.module = fragShaderModule;
    fragShaderStageCreateInfo.pName = "main";

    VkPipelineShaderStageCreateInfo shaderStages[] = {vertShaderStageCreateInfo, fragShaderStageCreateInfo};

    VkPipelineVertexInputStateCreateInfo vertexInputInfo = {};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = 1;
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attribDes.size());
    vertexInputInfo.pVertexBindingDescriptions = &bindingDes;
    vertexInputInfo.pVertexAttributeDescriptions = attribDes.data();

    VkPipelineInputAssemblyStateCreateInfo inputAssembly = {};
    inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
    inputAssembly.primitiveRestartEnable = VK_FALSE;

    VkViewport viewport = {};
    viewport.x = 0.0f;
    viewport.y = 0.0f;
    viewport.width = (float)swapChainExtent.width;
    viewport.height = (float)swapChainExtent.height;
    viewport.minDepth = 0.0f;
    viewport.maxDepth = 1.0f;

    VkRect2D scissor = {};
    scissor.offset = {0,0};
    scissor.extent = swapChainExtent;

    VkPipelineViewportStateCreateInfo viewportState = {};
    viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewportState.viewportCount = 1;
    viewportState.pViewports = &viewport;
    viewportState.scissorCount = 1;
    viewportState.pScissors = &scissor;

    VkPipelineRasterizationStateCreateInfo rasterizer = {};
    rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    rasterizer.depthClampEnable = VK_FALSE;//Enable to work with shadow maps?
    rasterizer.rasterizerDiscardEnable = VK_FALSE;
    rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
    rasterizer.lineWidth = 1.0f;
    rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
    rasterizer.frontFace = VK_FRONT_FACE_CLOCKWISE;
    rasterizer.depthBiasEnable = VK_FALSE;

    VkPipelineMultisampleStateCreateInfo multiSampling = {};
    multiSampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    multiSampling.sampleShadingEnable = VK_FALSE;
    multiSampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

    VkPipelineColorBlendAttachmentState colorBlendAttachment = {};
    colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT |
            VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
    colorBlendAttachment.blendEnable = VK_TRUE;
    colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
    colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
    colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
    colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
    colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
    colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

    VkPipelineColorBlendStateCreateInfo colorBlending = {};
    colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlending.logicOpEnable = VK_FALSE;
    colorBlending.logicOp = VK_LOGIC_OP_COPY;
    colorBlending.attachmentCount = 1;
    colorBlending.pAttachments = &colorBlendAttachment;
    colorBlending.blendConstants[0] = 0.0f;
    colorBlending.blendConstants[1] = 0.0f;
    colorBlending.blendConstants[2] = 0.0f;
    colorBlending.blendConstants[3] = 0.0f;

    VkDynamicState dynamicStates[] = {
            VK_DYNAMIC_STATE_VIEWPORT,
            VK_DYNAMIC_STATE_LINE_WIDTH
    };

    VkPipelineDynamicStateCreateInfo dynamicState = {};
    dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynamicState.dynamicStateCount = 2;
    dynamicState.pDynamicStates = dynamicStates;

    VkPipelineLayoutCreateInfo pipelineLayout = {};
    pipelineLayout.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;

    if(vkCreatePipelineLayout(vkDevice, &pipelineLayout, nullptr, &vkPipelineLayout) != VK_SUCCESS){
        throw std::runtime_error("Failed to create pipeline layout");
    }

    VkGraphicsPipelineCreateInfo pipelineInfo = {};
    pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    pipelineInfo.stageCount = 2;
    pipelineInfo.pStages = shaderStages;
    pipelineInfo.pVertexInputState = &vertexInputInfo;
    pipelineInfo.pInputAssemblyState = &inputAssembly;
    pipelineInfo.pViewportState = &viewportState;
    pipelineInfo.pRasterizationState = &rasterizer;
    pipelineInfo.pMultisampleState = &multiSampling;
    pipelineInfo.pDepthStencilState = nullptr;
    pipelineInfo.pColorBlendState = &colorBlending;
    pipelineInfo.pDynamicState = nullptr;

    pipelineInfo.layout = vkPipelineLayout;
    pipelineInfo.renderPass = vkRenderPass;
    pipelineInfo.subpass = 0;
    pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
    pipelineInfo.basePipelineIndex = -1;

    if(vkCreateGraphicsPipelines(vkDevice, VK_NULL_HANDLE, 1, &pipelineInfo,
            nullptr, &vkGraphicsPipeline) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan graphics pipeline");
    }





    vkDestroyShaderModule(vkDevice, vertShaderModule, nullptr);
    vkDestroyShaderModule(vkDevice, fragShaderModule, nullptr);

}

void Vulkan::createFrameBuffers() {
    swapChainFrameBuffer.resize(swapChainImageViews.size());

    VkFramebufferCreateInfo frameBufferInfo = {};
    frameBufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
    frameBufferInfo.renderPass = vkRenderPass;
    frameBufferInfo.width = swapChainExtent.width;
    frameBufferInfo.height = swapChainExtent.height;
    frameBufferInfo.layers = 1;

    for(size_t i = 0; i < swapChainFrameBuffer.size(); i++){
        VkImageView attachments[] = {
                swapChainImageViews[i]
        };

        frameBufferInfo.attachmentCount = 1;
        frameBufferInfo.pAttachments = attachments;

        if(vkCreateFramebuffer(vkDevice, &frameBufferInfo, nullptr, &swapChainFrameBuffer[i]) != VK_SUCCESS){
            throw std::runtime_error("Failed to create Vulkan frame buffer");
        }
    }

}

void Vulkan::createCommandPool() {
    QueueFamilyIndices indices = findQueueFamilies(vkPhysicalDevice, vkSurface);
    VkCommandPoolCreateInfo commandPoolInfo = {};
    commandPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    commandPoolInfo.queueFamilyIndex = indices.graphicsFamily.value();
    commandPoolInfo.flags = 0;

    if(vkCreateCommandPool(vkDevice, &commandPoolInfo, nullptr, &vkCommandPool) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan command pool");
    }
}

void Vulkan::createIndexBuffer() {
    void* data;
    VkDeviceSize bufferSize = sizeof(indies[0]) * indies.size();
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(bufferSize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer, stagingBufferMemory);

    vkMapMemory(vkDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

    memcpy(data, indies.data(), (size_t) bufferSize);

    vkUnmapMemory(vkDevice, stagingBufferMemory);

    createBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 vkIndexBuffer, vkIndexBufferMemory);

    copyBuffer(stagingBuffer, vkIndexBuffer, bufferSize);

    vkDestroyBuffer(vkDevice, stagingBuffer, nullptr);
    vkFreeMemory(vkDevice, stagingBufferMemory, nullptr);

}

void Vulkan::createVertexBuffer() {
    void* data;
    VkDeviceSize bufferSize = sizeof(verties[0]) * verties.size();
    VkBuffer stagingBuffer;
    VkDeviceMemory stagingBufferMemory;

    createBuffer(bufferSize,
            VK_BUFFER_USAGE_TRANSFER_SRC_BIT,
            VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
            stagingBuffer, stagingBufferMemory);


    vkMapMemory(vkDevice, stagingBufferMemory, 0, bufferSize, 0, &data);

    memcpy(data, verties.data(), (size_t) bufferSize);

    vkUnmapMemory(vkDevice, stagingBufferMemory);

    createBuffer(bufferSize,
                 VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                 VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
                 vkVertexBuffer, vkVertexBufferMemory);

    copyBuffer(stagingBuffer, vkVertexBuffer, bufferSize);

    vkDestroyBuffer(vkDevice, stagingBuffer, nullptr);
    vkFreeMemory(vkDevice, stagingBufferMemory, nullptr);

}

void Vulkan::createBuffer(VkDeviceSize deviceSize, VkBufferUsageFlags bufferUsage, VkMemoryPropertyFlags memoryProperties, VkBuffer& buffer, VkDeviceMemory& bufferMemory) {
    VkMemoryRequirements memoryRequirements;

    VkBufferCreateInfo bufferCreateInfo = {};
    bufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
    bufferCreateInfo.size = deviceSize;
    bufferCreateInfo.usage = bufferUsage;
    bufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

    if(vkCreateBuffer(vkDevice, &bufferCreateInfo, nullptr, &buffer) != VK_SUCCESS){
        throw std::runtime_error("Failed to create Vulkan vertex Command Buffer");
    }

    vkGetBufferMemoryRequirements(vkDevice, buffer, &memoryRequirements);

    VkMemoryAllocateInfo memoryAllocateInfo = {};
    memoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
    memoryAllocateInfo.allocationSize = memoryRequirements.size;
    memoryAllocateInfo.memoryTypeIndex = findMemoryTypes(memoryRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

    if(vkAllocateMemory(vkDevice, &memoryAllocateInfo, nullptr, &bufferMemory) != VK_SUCCESS){
        throw std::runtime_error("Failed to allocate physical device memory");
    }

    vkBindBufferMemory(vkDevice, buffer, bufferMemory, 0);


}

uint32_t Vulkan::findMemoryTypes(uint32_t typeFilter, VkMemoryPropertyFlags memoryPropertiesFlags){
    VkPhysicalDeviceMemoryProperties memoryProperties;
    vkGetPhysicalDeviceMemoryProperties(vkPhysicalDevice, &memoryProperties);

    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++){
        if((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & memoryPropertiesFlags) == memoryPropertiesFlags)
            return i;
    }

    throw std::runtime_error("Failed to find supported gpu memory type");

}

void Vulkan::createCommandBuffers() {
    commandBuffers.resize(swapChainFrameBuffer.size());
    VkClearValue clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
    VkBuffer vertexBuffers[] = {vkVertexBuffer};
    VkDeviceSize offsets[] = {0};


    VkCommandBufferAllocateInfo allocationInfo = {};
    allocationInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocationInfo.commandPool = vkCommandPool;
    allocationInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocationInfo.commandBufferCount = (uint32_t) commandBuffers.size();

    if(vkAllocateCommandBuffers(vkDevice, &allocationInfo, commandBuffers.data()) != VK_SUCCESS){
        throw std::runtime_error("Failed to allocate command buffers");
    }

    VkCommandBufferBeginInfo beginInfo = {};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0;
    beginInfo.pInheritanceInfo = nullptr;

    VkRenderPassBeginInfo renderPassInfo = {};
    renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassInfo.renderPass = vkRenderPass;
    renderPassInfo.renderArea.offset = {0,0};
    renderPassInfo.renderArea.extent = swapChainExtent;
    renderPassInfo.clearValueCount = 1;
    renderPassInfo.pClearValues = &clearColor;


    for(size_t i = 0; i < commandBuffers.size(); i++){
        if(vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS){
            throw std::runtime_error("Failed to begin to record commands");
        }
        renderPassInfo.framebuffer = swapChainFrameBuffer[i];

        vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

        vkCmdBindPipeline(commandBuffers[i], VK_PIPELINE_BIND_POINT_GRAPHICS, vkGraphicsPipeline);

        vkCmdBindVertexBuffers(commandBuffers[i], 0, 1, vertexBuffers, offsets);

        vkCmdBindIndexBuffer(commandBuffers[i], vkIndexBuffer, 0, VK_INDEX_TYPE_UINT16);

//        vkCmdDraw(commandBuffers[i], static_cast<uint32_t >(verties.size()),1,0,0);
        vkCmdDrawIndexed(commandBuffers[i], static_cast<uint32_t >(indies.size()), 1, 0, 0, 0);

        vkCmdEndRenderPass(commandBuffers[i]);

        if(vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS){
            throw std::runtime_error("Failed to record command buffer");
        }

    }
}

void Vulkan::createSyncObjects() {
    imageAvailableSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    renderFinishedSemaphore.resize(MAX_FRAMES_IN_FLIGHT);
    inFlightFence.resize(MAX_FRAMES_IN_FLIGHT);

    VkSemaphoreCreateInfo semaphoreInfo = {};
    semaphoreInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

    VkFenceCreateInfo fenceInfo = {};
    fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
    fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

    for(size_t i =0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        if (vkCreateSemaphore(vkDevice, &semaphoreInfo, nullptr, &imageAvailableSemaphore[i]) != VK_SUCCESS ||
            vkCreateSemaphore(vkDevice, &semaphoreInfo, nullptr, &renderFinishedSemaphore[i]) != VK_SUCCESS) {
            throw std::runtime_error("Failed to create Vulkan Semaphores");
        }
        if(vkCreateFence(vkDevice, &fenceInfo, nullptr, &inFlightFence[i]) != VK_SUCCESS){
            throw  std::runtime_error("Failed to create Vulkan Fence");
        }
    }
}

void Vulkan::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize bufferSize) {
    //Need to create temp command buffer just for the copy of buffers;

    VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
    commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    commandBufferAllocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    commandBufferAllocateInfo.commandPool = vkCommandPool;
    commandBufferAllocateInfo.commandBufferCount = 1;

    VkCommandBuffer commandBuffer;
    vkAllocateCommandBuffers(vkDevice, &commandBufferAllocateInfo, &commandBuffer);

    VkCommandBufferBeginInfo bufferBeginInfo = {};
    bufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    bufferBeginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;//We are gonna be waiting for this to finish before returning the function

    vkBeginCommandBuffer(commandBuffer, &bufferBeginInfo);

    VkBufferCopy copyRegion = {};
    copyRegion.srcOffset = 0;
    copyRegion.dstOffset = 0;
    copyRegion.size = bufferSize;

    vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);//Add a command to the command buffer

    vkEndCommandBuffer(commandBuffer);//We are done recording

    VkSubmitInfo cmdBufferSubmitInfo = {};
    cmdBufferSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    cmdBufferSubmitInfo.commandBufferCount = 1;
    cmdBufferSubmitInfo.pCommandBuffers = &commandBuffer;

    vkQueueSubmit(vkGraphicsQueue, 1, &cmdBufferSubmitInfo, VK_NULL_HANDLE);
    vkQueueWaitIdle(vkGraphicsQueue);

    vkFreeCommandBuffers(vkDevice, vkCommandPool, 1, &commandBuffer);
}

void Vulkan::mainLoop() {
    while(!glfwWindowShouldClose(glfwWindow)){
        glfwPollEvents();
        drawFrame();
    }

    vkDeviceWaitIdle(vkDevice);

}

void Vulkan::drawFrame() {
    vkWaitForFences(vkDevice, 1, &inFlightFence[currentFrame], VK_TRUE, UINT64_MAX);
    uint32_t imageIndex;
    VkSemaphore waitSemaphores[] = {imageAvailableSemaphore[currentFrame]};
    VkSemaphore signalSemaphores[] = {renderFinishedSemaphore[currentFrame]};
    VkSwapchainKHR swapChains[] = {vkSwapChain};
    VkPipelineStageFlags waitStages[] = {VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL};

    VkResult acquireImageResult = vkAcquireNextImageKHR(vkDevice, vkSwapChain, UINT64_MAX, imageAvailableSemaphore[currentFrame],
            VK_NULL_HANDLE, &imageIndex);

    if(acquireImageResult == VK_ERROR_OUT_OF_DATE_KHR){
        recreateSwapChain();
        return;
    }
    else if(acquireImageResult != VK_SUCCESS && acquireImageResult != VK_SUBOPTIMAL_KHR){
        throw std::runtime_error("Failed to acquire swap chain image");
    }

    VkSubmitInfo submitInfo = {};
    submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo.waitSemaphoreCount = 1;
    submitInfo.pWaitSemaphores = waitSemaphores;
    submitInfo.pWaitDstStageMask = waitStages;
    submitInfo.commandBufferCount = 1;
    submitInfo.pCommandBuffers = &commandBuffers[imageIndex];
    submitInfo.signalSemaphoreCount = 1;
    submitInfo.pSignalSemaphores = signalSemaphores;

    vkResetFences(vkDevice, 1, &inFlightFence[currentFrame]);

    if(vkQueueSubmit(vkGraphicsQueue, 1, &submitInfo, inFlightFence[currentFrame]) != VK_SUCCESS){
        throw std::runtime_error("Failed to submit draw command buffer");
    }


    VkPresentInfoKHR presentInfo = {};
    presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
    presentInfo.waitSemaphoreCount = 1;
    presentInfo.pWaitSemaphores = signalSemaphores;
    presentInfo.swapchainCount = 1;
    presentInfo.pSwapchains = swapChains;
    presentInfo.pImageIndices = &imageIndex;
    presentInfo.pResults = nullptr;

    VkResult presentQueueResult = vkQueuePresentKHR(vkPresentQueue, &presentInfo);

    if (presentQueueResult == VK_ERROR_OUT_OF_DATE_KHR) {
        frameBufferResized = false;
        recreateSwapChain();
    } else {
        if (presentQueueResult != VK_SUBOPTIMAL_KHR || frameBufferResized) {
            frameBufferResized = false;
            recreateSwapChain();
        } else {
            throw std::runtime_error("Failed to acquire swap chain image");
        }
    }


    vkQueueWaitIdle(vkPresentQueue);

    currentFrame = (currentFrame + 1) % MAX_FRAMES_IN_FLIGHT;
}

void Vulkan::cleanUpSwapChain() {
    for(auto frameBuffer : swapChainFrameBuffer){
        vkDestroyFramebuffer(vkDevice, frameBuffer, nullptr);
    }

    vkFreeCommandBuffers(vkDevice, vkCommandPool, static_cast<uint32_t >(commandBuffers.size()), commandBuffers.data());

    vkDestroyPipeline(vkDevice, vkGraphicsPipeline, nullptr);

    vkDestroyPipelineLayout(vkDevice, vkPipelineLayout, nullptr);

    vkDestroyRenderPass(vkDevice, vkRenderPass, nullptr);

    for(auto imageView : swapChainImageViews){
        vkDestroyImageView(vkDevice, imageView, nullptr);
    }

    vkDestroySwapchainKHR(vkDevice, vkSwapChain, nullptr);

}

void Vulkan::recreateSwapChain() {
    int width = 0, height = 0;
    while(width == 0 || height == 0){
        glfwGetFramebufferSize(glfwWindow, &width, &height);
        glfwWaitEvents();
    }
    vkDeviceWaitIdle(vkDevice);

    cleanUpSwapChain();

    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandBuffers();

}

void Vulkan::cleanUp() {

    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++) {
        vkDestroySemaphore(vkDevice, renderFinishedSemaphore[i], nullptr);
        vkDestroySemaphore(vkDevice, imageAvailableSemaphore[i], nullptr);
    }

    for(size_t i = 0; i < MAX_FRAMES_IN_FLIGHT; i++){
        vkDestroyFence(vkDevice, inFlightFence[i], nullptr);
    }

    cleanUpSwapChain();

    vkDestroyBuffer(vkDevice, vkVertexBuffer, nullptr);
    vkFreeMemory(vkDevice, vkVertexBufferMemory, nullptr);

    vkDestroyBuffer(vkDevice, vkIndexBuffer, nullptr);
    vkFreeMemory(vkDevice, vkIndexBufferMemory, nullptr);

    vkDestroyCommandPool(vkDevice, vkCommandPool, nullptr);

    vkDestroyDevice(vkDevice, nullptr);

    vkDestroySurfaceKHR(vkInstance,vkSurface, nullptr);

    if(enableValidationLayers){
        DestroyDebugUtilsMessengerEXT(vkInstance, debugBus, nullptr);
    }

    vkDestroyInstance(vkInstance, nullptr);


    glfwDestroyWindow(glfwWindow);

    glfwTerminate();

}


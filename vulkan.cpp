//Test file for vulkan
//This code is not for production
#include "vulkan.h"
#include "queueFamilies.hpp"
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

void Vulkan::run() {
    initWindow();
    initVulkan();
    mainLoop();
    cleanUp();
}

void Vulkan::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    glfwWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Vulkan", nullptr, nullptr);

}

void Vulkan::initVulkan() {
    createInstance();
    setUpDebugBus();
    pickPhysicalDevice();
    createLogicalDevice();

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

    supportedExtensions();
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

void Vulkan::supportedExtensions() {
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
    bool supportedGPU = false;
    QueueFamilyIndices indices = findQueueFamilies(physicalDevice);
    VkPhysicalDeviceProperties physicalDeviceProperties;
    VkPhysicalDeviceFeatures physicalDeviceFeatures;
    vkGetPhysicalDeviceProperties(physicalDevice, &physicalDeviceProperties);
    vkGetPhysicalDeviceFeatures(physicalDevice, &physicalDeviceFeatures);

    if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU){
        std::cout << "Integrated GPU found. \n\tNOTE: Performance might be poor if this is the only GPU available on your system" << std::endl;
        supportedGPU = true;
    }
    else if(physicalDeviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU){
        std::cout << "Dedicated GPU found" << std::endl;
        supportedGPU = true;
    }
    if(!indices.isComplete()){
        std::cout << "GPU does NOT support Vulkan commands" << std::endl;
    }


//    return supportedGPU && physicalDeviceFeatures.geometryShader;
    return supportedGPU && indices.isComplete();
}

void Vulkan::createLogicalDevice() {
    QueueFamilyIndices indices = findQueueFamilies(vkPhysicalDevice);

    VkDeviceQueueCreateInfo queueCreateInfo = {};
    queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
    queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
    queueCreateInfo.queueCount = 1;//We break as soon as we find a valid queue
    float queuePriority = 1.0f;
    queueCreateInfo.pQueuePriorities = &queuePriority;//Floats take up a lot of space so we want to pass by reference

    VkPhysicalDeviceFeatures physicalDeviceFeatures = {};

    VkDeviceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    createInfo.pQueueCreateInfos = &queueCreateInfo;
    createInfo.queueCreateInfoCount = 1;
    createInfo.pEnabledFeatures = &physicalDeviceFeatures;
    createInfo.enabledExtensionCount = 0;

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

    vkGetDeviceQueue(vkDevice, indices.graphicsFamily.value(), 0, &vkQueue);



}

void Vulkan::mainLoop() {
    while(!glfwWindowShouldClose(glfwWindow)){
        glfwPollEvents();
    }

}

void Vulkan::cleanUp() {
    if(enableValidationLayers){
        DestroyDebugUtilsMessengerEXT(vkInstance, debugBus, nullptr);
    }
    vkDestroyDevice(vkDevice, nullptr);

    vkDestroyInstance(vkInstance, nullptr);


    glfwDestroyWindow(glfwWindow);

    glfwTerminate();

}


#include "vulkanMain.hpp"
//#include "../plexiHelper.hpp"
#include "./VulkanHelpers/validationLayers.hpp"

//Vulkan::Vulkan(){//Commented out rn be using trivial default instead
//
//}

bool Vulkan::setRequiredInformation(const char **EXTENSIONS, const size_t EXT_SIZE, const char* name) {
    if(EXT_SIZE <= 0){
        std::cerr << "ERROR: Required Extensions are missing data: Required Extension Length > 0" << std::endl;
        return false;
    }

    requiredExtensions.reserve(EXT_SIZE);

    for(size_t i = 0; i < EXT_SIZE; i++){
        requiredExtensions.push_back(EXTENSIONS[i]);
    }

    this->applicationName = name;
    requiredExtensionsSet = true;
    return true;
}

void Vulkan::setOptionInformation(const char **VALIDATION_LAYERS, const size_t VALID_LAYER_SIZE,
                                  const char **EXTENSIONS, const size_t EXT_SIZE) {
    if(EXT_SIZE < 0){
        std::cerr << "ERROR: Optional Extensions are missing data: Optional Extension Length >= 0" << std::endl;
    }
    if(VALID_LAYER_SIZE < 0){
        std::cerr << "ERROR: Optional Validation Layers are missing data: Optional Validation Length >= 0" << std::endl;
    }

    //Todo: Warning if length = 0

    optionalExtensions.reserve(EXT_SIZE);
    optionalValidationLayers.reserve(VALID_LAYER_SIZE);

    for(size_t i = 0; i < EXT_SIZE; i++){
        optionalExtensions.push_back(EXTENSIONS[i]);
    }

    for(size_t i = 0; i < VALID_LAYER_SIZE; i++){
        optionalValidationLayers.push_back(VALIDATION_LAYERS[i]);
    }

    validationLayersEnabled = optionalValidationLayers.empty();


}

std::vector<const char*> Vulkan::getRequiredExtensions() {
    uint32_t glfwExtensionsCount = 0;
    const char** glfwExtensions;
    std::vector<const char*> extensions;


    glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionsCount);

    extensions.reserve(glfwExtensionsCount);

    for(size_t i = 0; i < glfwExtensionsCount; i++){
        extensions.push_back(glfwExtensions[i]);
    }

    if(validationLayersEnabled){
        extensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    }

    //Maybe add status message here

    return extensions;
}

void Vulkan::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    glfwWindow = glfwCreateWindow(800, 600, applicationName, glfwGetPrimaryMonitor(), nullptr);//Makes full screen w/ res 800x600

    glfwSetWindowUserPointer(glfwWindow, this);

//    glfwSetFramebufferSizeCallback(glfwWindow, frameBufferResizeCallBack);//TODO: Implement Later


}


bool Vulkan::createInstance() {
    if(!requiredExtensionsSet) {
        std::cerr << "ERROR: No Vulkan Extensions have been set: Ensure that required extensions are set in Plexi Config" << std::endl;
        return false;
    }
    auto extensions = getRequiredExtensions();

    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = applicationName;
    appInfo.applicationVersion = VK_MAKE_VERSION(0,1,0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    VkInstanceCreateInfo instanceInfo = {};
    instanceInfo.sType  = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instanceInfo.pApplicationInfo = &appInfo;
    instanceInfo.enabledExtensionCount = static_cast<uint32_t>(requiredExtensions.size());
    instanceInfo.ppEnabledExtensionNames = extensions.data();
    if(validationLayersEnabled){
        instanceInfo.enabledLayerCount = static_cast<uint32_t>(optionalValidationLayers.size());
        instanceInfo.ppEnabledLayerNames = extensions.data();
    } else{
        instanceInfo.enabledLayerCount = 0;
    }

    VkResult err = vkCreateInstance(&instanceInfo, nullptr, &vulkanInstance);
    if(err != VK_SUCCESS){
        std::cerr << "ERROR: Failed to create Vulkan instance: Device or required extensions may not be supported. Check Plexi Config. VK Error Code: " << err << std::endl;
        return false;
    }

    return true;
}

bool Vulkan::isSupported() {
    if(!requiredExtensionsSet) {
        std::cerr << "ERROR: No Vulkan Extensions have been set: Ensure that required extensions are set in Plexi Config" << std::endl;
        return false;
    }

    //validation layer support - Extensions are checked in the instance
    if(validationLayersEnabled){
        if(!checkValidationLayerSupport(optionalValidationLayers)) {
            std::cerr << "WARNING: Validation Layers requested but unsupported: Verify device support and check Plexi Config" << std::endl;
            validationLayersEnabled = false;
        }
    }

    initWindow();

    return createInstance();
}

GLFWwindow *Vulkan::getWindow() {
    return GLFWwindow*;
}

bool Vulkan::initBackend() {


    return false;
}

void Vulkan::runBackend() {
    while(!glfwWindowShouldClose(glfwWindow)){
        glfwPollEvents();
    }

}

void Vulkan::destroyWindow() {
    glfwDestroyWindow(glfwWindow);
    glfwTerminate();
}

void Vulkan::cleanup() {
    //clean Up all other stuff up here
    vkDestroyInstance(vulkanInstance, nullptr);

    destroyWindow();
}

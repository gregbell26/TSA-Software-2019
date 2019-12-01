#include "acrylic_plexiRenderer_core.hpp"

#include <GLFW/glfw3.h>

int main(){
    Plexi::initPlexi();
    glfwSwapInterval(30);
    while(!glfwWindowShouldClose(Plexi::getWindowRef())){
        glfwPollEvents();
        Plexi::onUpdate();
        glfwSwapBuffers(Plexi::getWindowRef());
    }


//    std::cin.get();
    Plexi::cleanupPlexi();



    return 0;
}
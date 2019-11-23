#define PLEXI_USE_LIB

#include "./PlexiBackend/plexiHelper.hpp"
#include "PlexiBackend/acrylic_plexiBackend.hpp"
#include "plexi_usrStructs.hpp" //All structs to work with plexi are defined here

#include "acrylic_plexiRenderer.hpp"


int main(void){
    Plexi::initPlexi();
    //GLFWwindow* window = Plexi::GFXBackendMap[Plexi::activeConfig->activeBackendName]->getWindowRef();
    Plexi::cleanupPlexi();
    return 0;
}
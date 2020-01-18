#include "OpenGLMain.cpp"

void OpenGL::cleanUpGraphicsPipeline(const std::string& pipelineName) {
    if(pipelineName == "all"){
        logInformation("Cleaning up all pipelines...")
        for(auto& [pipeline, componentMap] : activePipelines){
            logInformation("\tCleaning up graphics pipeline \'" + pipeline + "\'")
            glDeleteProgram(componentMap[SHADER_PROGRAM]);
            componentMap[SHADER_PROGRAM] = 0;
            glDeleteBuffers(1, &componentMap[VERTEX_BUFFER]);
            componentMap[VERTEX_BUFFER] = 0;
            glDeleteBuffers(1, &componentMap[INDEX_BUFFER]);
            componentMap[INDEX_BUFFER] = 0;
            glDeleteVertexArrays(1, &componentMap[VERTEX_ARRAY]);
            componentMap[VERTEX_ARRAY] = 0;
            componentMap.clear();
        }
        activePipelines.clear();
        return;
    }

    try {
        logInformation("Cleaning up graphics pipeline \'" + pipelineName + "\'")
        pipelineComponentMap &tempMap = activePipelines.at(pipelineName);
        glDeleteProgram(tempMap[SHADER_PROGRAM]);
        tempMap[SHADER_PROGRAM] = 0;
        glDeleteBuffers(1, &tempMap[VERTEX_BUFFER]);
        tempMap[VERTEX_BUFFER] = 0;
        glDeleteBuffers(1, &tempMap[INDEX_BUFFER]);
        tempMap[INDEX_BUFFER] = 0;
        glDeleteVertexArrays(1, &tempMap[VERTEX_ARRAY]);
        tempMap[VERTEX_ARRAY] = 0;
        tempMap.clear();
    } catch (std::out_of_range& err){
        logWarning("Pipeline \'" + pipelineName + "\' does not exist. Please check your spelling.")
        logWarning("Error details: " + std::string() + err.what())
        return;
    }

}

void OpenGL::removeTexture() {

}

void OpenGL::removeTexture(uint32_t textureId) {

}

void OpenGL::removeFont() {

}

void OpenGL::removeFont(uint32_t fontId) {

}


void OpenGL::cleanup() {
    cleanUpGraphicsPipeline("all");
    glfwDestroyWindow(glfwWindow);

    glfwTerminate();
}

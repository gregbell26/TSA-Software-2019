#define PLEXI_LIBRARY_ACTIVE
#include  "../plexi_shaders.hpp"
#include "../plexi_buffer.hpp"
#include "../plexi_helper.hpp"

#include "OpenGL2DTexture.hpp"

#include "OpenGLMain.hpp"


struct Cache {//For some reason having these elements inside of the class leads to them not holding data but putting them out here works
            //Have no clue as to why this is -- Need to investigate further
    std::vector<Plexi2DTexture*> textureCache = {};
    std::vector<std::map<GLchar, OpenGL::Character>> fontFaceCache = {};
    std::vector<StandardRenderTask> standardRenderTaskCache = {};
    std::vector<TextRenderTask> textRenderTasksCache = {};

};

auto *cache = new Cache;

static void glfwErrorCallBack(int errorCode, const char* description){
    if(errorCode == GLFW_NO_ERROR){
        return;
    }

    logError("GLFW Error: " + std::to_string(errorCode) + ':' + description)
    //todo handle errors
}

#if !defined(MACOS)
static void GLAPIENTRY openGLDebugMessageCallBack(GLenum source,
                                                  GLenum type,
                                                  GLuint id,
                                                  GLenum severity,
                                                  GLsizei length,
                                                  const char* message,
                                                  const void* userParam){
    if(type == GL_DEBUG_TYPE_ERROR)
        logError("OpenGL Error: " + std::string() + message)
    else
        logInformation("OpenGL Message: " + std::string() + message)

}
#endif

bool OpenGL::setRequiredInformation(const PlexiGFX_RequiredInformation &requiredInformation) {
    appName = requiredInformation.appName.c_str();
    requiredInfoSet = true;
    return true;
}

void OpenGL::setOptionInformation(const PlexiGFX_OptionalInformation &optionalInformation) {

}

bool OpenGL::createWindow() {
    if(!glfwInit()){
        logError("Failed to initialize GLFW")
        return false;
    }
    logInformation("Initialized GLFW successfully")
    //Enforces OpenGL 4.1 on mac and windows
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glfwSetErrorCallback(glfwErrorCallBack);

    glfwWindow = glfwCreateWindow(1280, 720, appName, nullptr, nullptr);

    if(!glfwWindow){
        logError("Failed to create GLFW window")
        glfwTerminate();
        return false;
    }
    //Im sure that there is more that needs to be done

    logInformation("Created GLFW window successfully")
    return true;
}

bool OpenGL::initCore() {
    glfwMakeContextCurrent(glfwWindow);
    bool glStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

#if !defined(MACOS)//OpenGL debugging is not supported on macOS
    glEnable(GL_DEBUG_OUTPUT);
    logInformation("Using OpenGL debug messages")
    glDebugMessageCallback(openGLDebugMessageCallBack, nullptr);
#endif

    if(!glStatus)
        logError("Failed to initialized OpenGL")
    else {
        logInformation("Initialized OpenGL successfully")
        logInformation("OpenGL Info: ")
        logInformation("\tGPU Vendor: " + std::string() + (const char*) glGetString(GL_VENDOR))
        logInformation("\tGPU Name: " + std::string() + (const char*) glGetString(GL_RENDERER))
        logInformation("\tOpenGL Version: " + std::string() + (const char*) glGetString(GL_VERSION))
    }

    //Todo version check
    return glStatus;
}

bool OpenGL::isSupported() {

    return requiredInfoSet && createWindow() && initCore();
}


bool OpenGL::initBackend() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);


    return true;
}

bool OpenGL::createVertexBuffer(const float *vertices, const size_t &size, const bool& dynamicMode, pipelineComponentMap& pipelineMap) {
    glGenBuffers(1, &pipelineMap[VERTEX_BUFFER]);
    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[VERTEX_BUFFER]);
    if(!dynamicMode)
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    else
        glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);

    //Todo check for errors - Pos add error Callback?
    return true;
}

bool OpenGL::createIndexBuffer(const uint32_t *indices, const size_t &size, pipelineComponentMap& pipelineMap) {
    glGenBuffers(1, &pipelineMap[INDEX_BUFFER]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

    return true;
}

bool OpenGL::createVertexArray(const Plexi::Buffer::BufferCreateInfo &bufferCreateInfo, pipelineComponentMap& pipelineMap) {
    if(bufferCreateInfo.getLayout().getBufferElements().empty()){
        logError("Buffer Layout is empty")
        return false;
    }

    glGenVertexArrays(1, &pipelineMap[VERTEX_ARRAY]);//I have no idea why its called gen and not create

    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ARRAY_BUFFER, pipelineMap[VERTEX_BUFFER]);

    const auto& bufferLayout = bufferCreateInfo.getLayout();
    uint8_t vertexBufferIndex = 0;
    for(const auto& element : bufferLayout){
        glEnableVertexAttribArray(vertexBufferIndex);

        glVertexAttribPointer(
                vertexBufferIndex,
                Plexi::Shaders::getDataTypeCount(element.dataType),
                Plexi::Shaders::convertDataTypeToGLSLBaseType(element.dataType),
                element.normalized ? GL_TRUE : GL_FALSE,
                bufferLayout.getStride(),
                (const void*) element.offset
        );
        //todo Add error check
        vertexBufferIndex++;
    }

//    glBindVertexArray(pipelineMap[VERTEX_ARRAY]);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pipelineMap[INDEX_BUFFER]);

    return true;

}

void OpenGL::createGraphicsPipeline(const Plexi::Shaders::ShaderCreateInfo& shaderCreateInfo, const Plexi::Buffer::BufferCreateInfo& bufferCreateInfo) {
    logInformation("Attempting to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")

    if(!shaderCreateInfo.isComplete()){
        //Error message Already displayed. We don't need to do it again
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    //Create Pipeline
    pipelineComponentMap pipelineMap = {
            {SHADER_PROGRAM, 0},
            {VERTEX_BUFFER, 0},
            {INDEX_BUFFER, 0},
            {VERTEX_ARRAY, 0}
    };

    logInformation("Attempting to create OpenGL Shader Program \'" + shaderCreateInfo.shaderName + "\'")
    if(!createShaders(shaderCreateInfo.glslVertexCode, shaderCreateInfo.glslFragmentCode, shaderCreateInfo.shaderName, pipelineMap)){
        logWarning("Failed to create OpenGL Shader Program \'" + shaderCreateInfo.shaderName + "\'")
        pipelineMap.clear();
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    logInformation("Shader Program created successfully")

    createVertexBuffer(bufferCreateInfo.vertexArray, bufferCreateInfo.vertexArraySize, bufferCreateInfo.dynamicBuffer, pipelineMap);

    createIndexBuffer(bufferCreateInfo.indexArray, bufferCreateInfo.indexArraySize, pipelineMap);

    //Todo Move this vertex array stuff into a struct or something

    if(!createVertexArray(bufferCreateInfo, pipelineMap)){
        logInformation("Failed to create OpenGL Vertex Array")
        glDeleteProgram(pipelineMap[SHADER_PROGRAM]);
        pipelineMap[SHADER_PROGRAM] = 0;
        glDeleteBuffers(1, &pipelineMap[VERTEX_BUFFER]);
        pipelineMap[VERTEX_BUFFER] = 0;
        glDeleteBuffers(1, &pipelineMap[INDEX_BUFFER]);
        pipelineMap[INDEX_BUFFER] = 0;
        glDeleteVertexArrays(1, &pipelineMap[VERTEX_ARRAY]);
        pipelineMap[VERTEX_ARRAY] = 0;
        pipelineMap.clear();
        logWarning("Failed to create \'" + bufferCreateInfo.shaderName + "\' graphics pipeline")
        return;
    }

    activePipelines.insert(std::pair(bufferCreateInfo.shaderName, pipelineMap));//Not passing by ref bc we need this always

    logInformation("Created \'" + bufferCreateInfo.shaderName + "\' Graphics Pipeline Successfully")

    glUseProgram(pipelineMap[SHADER_PROGRAM]);

    setInt(bufferCreateInfo.shaderName, "texture2D", 0);//Tell openGL we have will want to use this shader slot

    glUseProgram(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void OpenGL::setClearColor(const float &r, const float &g, const float &b, const float &a) {
    glClearColor(r,g,b,a);
}

void OpenGL::submitScene(const std::vector<StandardRenderTask>& standardRenderTasks) {
    //Def wanna optimize this
    if(cache->standardRenderTaskCache.size() != standardRenderTasks.size()){
        cache->standardRenderTaskCache.resize(standardRenderTasks.size());
    }
//    else if(std::equal(cache.standardRenderTaskCache.begin(), cache.standardRenderTaskCache.begin() + cache.standardRenderTaskCache.size(), standardRenderTasks.begin())){//Might need to do std::equals for this
//        return;
//    }
    for(size_t i = 0; i < standardRenderTasks.size(); i++) {
        cache->standardRenderTaskCache[i] = standardRenderTasks[i];
    }

}

void OpenGL::submitScene(const std::vector<TextRenderTask> &textRenderTasks) {
    //Def wanna optimize this
    if(cache->textRenderTasksCache.size() != textRenderTasks.size()){
        cache->textRenderTasksCache.resize(textRenderTasks.size());
    }
//    else if(std::equal(cache.standardRenderTaskCache.begin(), cache.standardRenderTaskCache.begin() + cache.standardRenderTaskCache.size(), textRenderTasks.begin())){//Might need to do std::equals for this
//        return;
//    }
    for(size_t i = 0; i < textRenderTasks.size(); i++) {
        cache->textRenderTasksCache[i] = textRenderTasks[i];
    }
}

void OpenGL::onUpdate() {
    clear();
    if((cache->textureCache.empty() && cache->fontFaceCache.empty()) || activePipelines.empty()) {
        if(onUpdateErrorCounter >= 240){
            logWarning("Unable to render. Graphics pipeline and/or texture cache is empty")//Def Wanna async this
            onUpdateErrorCounter = 0;
        }
        onUpdateErrorCounter++;
        glfwSwapBuffers(glfwWindow);
        return;
    }

    if(cache->standardRenderTaskCache.empty() && cache->textRenderTasksCache.empty()){
        glfwSwapBuffers(glfwWindow);
        return;
    }

    if(!cache->standardRenderTaskCache.empty()){

        for(const auto& stdRenderTask : cache->standardRenderTaskCache){

            glUseProgram(activePipelines[stdRenderTask.graphicsPipelineName][SHADER_PROGRAM]);
            setMat4(stdRenderTask.graphicsPipelineName, "viewProjection", glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, -1.0f, 1.0f));

            for(unsigned short i = 0; i < stdRenderTask.textureCount; i++){
                try {
                    cache->textureCache.at(stdRenderTask.textureIds[i])->bind(i);
                } catch(std::out_of_range& err){
                    if(onUpdateErrorCounter >= 240){
                        logWarning("Texture id: " + std::to_string(stdRenderTask.textureIds[i]) + "does not exist")
                        onUpdateErrorCounter = 0;
                    }
                    continue;
                }
            }

            setFloat4(stdRenderTask.graphicsPipelineName, "color", stdRenderTask.RGBAColor);
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), stdRenderTask.position) * glm::scale(glm::mat4x4(1.0f), {stdRenderTask.scale, 0.0f});

            setMat4(stdRenderTask.graphicsPipelineName, "transform", transform);
            glBindVertexArray(activePipelines[stdRenderTask.graphicsPipelineName][VERTEX_ARRAY]);
            glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, nullptr);

            for(unsigned short i = 0; i < stdRenderTask.textureCount; i++){
                try {
                    cache->textureCache.at(stdRenderTask.textureIds[i])->unbind();
                }catch(std::out_of_range& err){
                    if(onUpdateErrorCounter >= 240){
                        logWarning("Texture id: " + std::to_string(stdRenderTask.textureIds[i]) + "does not exist")
                        onUpdateErrorCounter = 0;
                    }
                    continue;
                }
            }
        }

        glUseProgram(0);
        glBindVertexArray(0);
    }

    if(!cache->textRenderTasksCache.empty()){
        for(const auto& txtRenderTask : cache->textRenderTasksCache){
            glUseProgram(activePipelines[txtRenderTask.graphicsPipelineName][SHADER_PROGRAM]);
            setMat4(txtRenderTask.graphicsPipelineName, "viewProjection", glm::ortho(-50.0f, 50.0f, -50.0f, 50.0f, -1.0f, 1.0f));
            auto &fontFace = cache->fontFaceCache[txtRenderTask.fontName];

            setFloat4(txtRenderTask.graphicsPipelineName, "color", txtRenderTask.RGBAColor);
            glBindVertexArray(activePipelines[txtRenderTask.graphicsPipelineName][VERTEX_ARRAY]);

            std::string::const_iterator i;
            float nextCharLoc = txtRenderTask.position.x;

            for(i = txtRenderTask.text.begin(); i != txtRenderTask.text.end(); i++){
                auto activeChar = fontFace[*i];
                float xPos = (nextCharLoc + activeChar.bearing.x * txtRenderTask.scale)/1.5f;
                float yPos =  txtRenderTask.position.y - (activeChar.size.y - activeChar.bearing.y) * txtRenderTask.scale;
                float width = (activeChar.size.x/1.5f) * txtRenderTask.scale;
                float height = activeChar.size.y * txtRenderTask.scale;

                float newVertexBuffer[6][4] {
                        {xPos, yPos+height,         0.0f, 0.0f},
                        {xPos, yPos,                0.0f, 1.0f},
                        {xPos+width, yPos,          1.0f, 1.0f},
                        {xPos, yPos+height,         0.0f, 0.0f},
                        {xPos+width, yPos,          1.0f, 1.0f},
                        {xPos+width, yPos+height,   1.0f, 0.0f},


                };

                glBindTexture(GL_TEXTURE_2D, activeChar.glTextureId);
                glBindBuffer(GL_ARRAY_BUFFER, activePipelines[txtRenderTask.graphicsPipelineName][VERTEX_BUFFER]);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newVertexBuffer), newVertexBuffer);
                glBindBuffer(GL_ARRAY_BUFFER, 0);

                glDrawArrays(GL_TRIANGLES, 0, 6);

                nextCharLoc += (activeChar.glAdvance >> 6) * txtRenderTask.scale;
            }
        }

        glUseProgram(0);
        glBindVertexArray(0);

    }

    glfwSwapBuffers(glfwWindow);

}


void OpenGL::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGL::addTexture(Plexi2DTexture* texture) {
    cache->textureCache[texture->getId()] = texture;//might not be necessary
}

Plexi2DTexture* OpenGL::getNewTexture() {
    cache->textureCache.push_back(new OpenGL2DTexture(cache->textureCache.size()));

    return cache->textureCache[cache->textureCache.size() - 1];
}

uint32_t OpenGL::addFontFace(FT_Face &fontFace, uint32_t charCount) {
    std::map<GLchar, OpenGL::Character> charMap;
    logInformation("Loading " + std::to_string(charCount) + " font characters into openGL")

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for(GLubyte c = 0; c < charCount; c++){
        if(FT_Load_Char(fontFace, c, FT_LOAD_RENDER) != FT_Err_Ok){
            logError("An error occurred while loading characters")
            continue;
        }
        GLuint glTextId;
        glGenTextures(1, &glTextId);
        glBindTexture(GL_TEXTURE_2D, glTextId);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            fontFace->glyph->bitmap.width,
            fontFace->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            fontFace->glyph->bitmap.buffer
        );

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        Character character = {
            glTextId,
            glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
            glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top),
            static_cast<uint32_t>(fontFace->glyph->advance.x)
        };

        charMap.insert(std::pair<GLchar, Character>(c, character));
    }

//    std::cout << fontFace->family_name << std::endl;

    cache->fontFaceCache.resize(cache->fontFaceCache.size()+1);
    cache->fontFaceCache[cache->fontFaceCache.size()-1] = charMap;

//    cache->fontFaceCache.insert(std::pair<std::string, std::map<GLchar, OpenGL::Character> >(fontFace->family_name, charMap));

    return static_cast<uint32_t>(cache->fontFaceCache.size()-1);
}

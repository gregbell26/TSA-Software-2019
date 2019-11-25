#include <iostream>
#include "shaders.hpp"

Plexi::Shader Plexi::Shaders::compileShaderFromString(const string &shaderName, const string &code, bool optimizeOutput) {
    return Shader();
}

Plexi::Shader Plexi::Shaders::compileShaderFromFile(const string &shaderName, bool optimizeOutput, bool deleteSrc) {
    return Shader();
}

void Plexi::Shaders::outputShader(const Shader &shader) {
    std::cerr << "Writing shaders is currently unsupported" << std::endl;
    return;

    std::ofstream fout((DEFAULT_SHADER_PATH + shader.name + DEFAULT_COMPILED_EXTENSION), std::ios::binary);

    if(!fout.is_open()){
        std::cerr << "Failed to open file for writing" << std::endl;
        return;
    }

//    if((size_t) sizeof(shader.byteCode) != shader.codeSize){
//        std::cout << "Warning: Shader size does not equal given size. Using given size" << std::endl;
//    }
//
//    fout.write((char *) &shader.byteCode, shader.codeSize); //Might have to convert this differently from 4 byte blocks to 1 byte blocks
    fout.close();

}

Plexi::Shader Plexi::Shaders::loadShader(const std::filesystem::path &shaderPath) {
    std::cout << "Attempting to load compiled shader from " << shaderPath << "." << std::endl;
    Shader shader = {};
    std::ifstream fin(shaderPath, std::ios::ate | std::ios::binary);

    if(!fin.is_open()){
        std::cerr << "Failed to open compiled shader at " << shaderPath << std::endl;
        std::cout << "Unloaded shader returned" << std::endl;
        return shader;
    }

    size_t fileSize = (size_t)fin.tellg();//Returns the cursor pos which is at end of file for loading in ate thus being the size
    std::vector<char> loadedBuffer(fileSize);

    fin.seekg(0);//Move to top of file

    fin.read(loadedBuffer.data(), fileSize);//Load into loadedBuffer w/ size fileSize

    fin.close();

//    shader.byteCode = loadedBuffer.data();
    shader.codeSize = loadedBuffer.size();
    shader.code = reinterpret_cast<const uint32_t *>(loadedBuffer.data());
    shader.name = shaderPath.filename().string();



    shader.name.erase(shader.name.find( '.'));
    std::cout << "Compiled shader \'" << shader.name << "\' loaded." << std::endl;

    return shader;
}

Plexi::Shader Plexi::Shaders::loadShader(const string &shaderName) {
    std::filesystem::path shaderPath;

    shaderPath.assign(DEFAULT_SHADER_PATH + shaderName + DEFAULT_COMPILED_EXTENSION);

    return loadShader(shaderPath);
}

bool Plexi::Shaders::checkForPrecompiledShaders(const string &shaderName, Shader& outputShader) {
    std::filesystem::path pathToCheck;
    bool exists = false;
    std::cout << "Searching for shader \'" << shaderName << "\'"<< std::endl;
    for(const auto &EXTENSION : RECOGNIZED_COMPILED_EXTENSIONS){
        pathToCheck.assign(DEFAULT_SHADER_PATH + shaderName); //Reset to default
        pathToCheck += EXTENSION; // Add extension
        std::cout << "\tSearching " << pathToCheck << std::endl;
        if(std::filesystem::exists(pathToCheck)){
            exists = true;
            break;
        }
    }

    if(exists){
        std::cout << "Precompiled shader \'" << shaderName << "\' found at: " << pathToCheck << std::endl;
        outputShader = loadShader(pathToCheck);
        //Todo: Set Shader type
    } else {
        std::cerr << "Failed to locate precompiled shader \'" << shaderName << "\' with default search paths" << std::endl;
    }




    return exists;
}
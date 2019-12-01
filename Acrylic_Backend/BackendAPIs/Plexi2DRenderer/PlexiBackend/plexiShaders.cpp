#include "plexiShaders.hpp"

GLenum Plexi::Shaders::convertDataTypeToGLSLBaseType(const DataType &dataType) {
    switch(dataType){
        case DataType::Float:
            return GL_FLOAT;
        case DataType::Float2:
            return GL_FLOAT;
        case DataType::Float3:
            return GL_FLOAT;
        case DataType::Float4:
            return GL_FLOAT;
        case DataType::Int:
            return GL_INT;
        case DataType::Int2:
            return GL_INT;
        case DataType::Int3:
            return GL_INT;
        case DataType::Int4:
            return GL_INT;
        case DataType::Bool:
            return GL_BOOL;
        case DataType::Mat3:
            return GL_FLOAT;
        case DataType::Mat4:
            return GL_FLOAT;
        default:
            std::cerr << "Unrecognised data type" << std::endl;
            return 0;
    }

}

uint32_t Plexi::Shaders::getDataTypeSize(const Plexi::Shaders::DataType &dataType) {
    switch(dataType){
        case DataType::Float://1 X 4
            return 4;
        case DataType::Float2:
            return 8;
        case DataType::Float3:
            return 12;
        case DataType::Float4:
            return 16;
        case DataType::Int://1 X 4
            return 4;
        case DataType::Int2:
            return 8;
        case DataType::Int3:
            return 12;
        case DataType::Int4:
            return 16;
        case DataType::Bool://1 X 1
            return 1;
        case DataType::Mat3://4 X 3 X 3
            return 36;
        case DataType::Mat4://4 X 4 X 4
            return 64;
        default:
            std::cerr << "Unrecognised Data Type" << std::endl;
            return 0;
    }
}

uint32_t Plexi::Shaders::getDataTypeCount(const Plexi::Shaders::DataType &dataType) {
    switch(dataType){
        case DataType::Float:
            return 1;
        case DataType::Float2:
            return 2;
        case DataType::Float3:
            return 3;
        case DataType::Float4:
            return 4;
        case DataType::Int:
            return 1;
        case DataType::Int2:
            return 2;
        case DataType::Int3:
            return 3;
        case DataType::Int4:
            return 4;
        case DataType::Bool:
            return 1;
        case DataType::Mat3:
            return 9;
        case DataType::Mat4:
            return 16;
        default:
            std::cerr << "Unrecognised Data Type" << std::endl;
            return 0;
    }}

string Plexi::Shaders::loadGLSLShaderFromFile(const std::filesystem::path &shaderPath) {
    if(!std::filesystem::exists(shaderPath) || !(shaderPath.has_filename() && shaderPath.has_extension())){
        std::cerr << "Invalid shader path provided" << std::endl;
        return string();
    }
    std::ifstream fin(shaderPath);
    if(!fin.is_open()){
        std::cerr << "An error occurred when attempting to open " << shaderPath << std::endl;
        return string();
    }
    string loadedShader;
    while(std::getline(fin, loadedShader)){

    }
    fin.close();
    return loadedShader;
}

uint32_t *Plexi::Shaders::loadSPIRVShaderFromFile(const std::filesystem::path &shaderPath) {
    if(!std::filesystem::exists(shaderPath) || !(shaderPath.has_filename() && shaderPath.has_extension())){
        std::cerr << "Invalid shader path provided" << std::endl;
        return nullptr;
    }
    std::ifstream fin(shaderPath);
    if(!fin.is_open()){
        std::cerr << "An error occurred when attempting to open " << shaderPath << std::endl;
        return nullptr;
    }

    //Todo finish this function
    return nullptr;
}

std::filesystem::path Plexi::Shaders::locateShader(const std::filesystem::path &pathToSearch, const string &shaderName,
                                                   Plexi::Shaders::ShaderLanguage shaderType) {
    std::filesystem::path currentSearchPath;
    std::filesystem::path validResult;
    uint32_t possMatches = 0;
    std::cout << "Attempting to locate shader \'" << shaderName << "\' in " << pathToSearch << std::endl;

    if(pathToSearch.has_filename() && pathToSearch.has_extension()){//If the path provided is a valid shader path
        if(std::filesystem::exists(pathToSearch)) {
            return pathToSearch;
        }
        else {
            std::cerr << "Invalid shader path provided" << std::endl;
            //Poss make path valid
            return std::filesystem::path();
        }
    }
    for(const auto & extension : RECOGNISED_EXTENSIONS[shaderType]){
        currentSearchPath.assign(pathToSearch);
        currentSearchPath += shaderName;
        currentSearchPath += extension;
        if(std::filesystem::exists(currentSearchPath)){
            std::cout << "Possible match found at " << currentSearchPath << std::endl;
            possMatches++;
            validResult = currentSearchPath;
        }
    }

    if(possMatches != 1) {
        std::cout << "Warning: There were " << possMatches << " possible matches located. Using " << validResult;
    }

    if(possMatches == 0){
        std::cerr << "No matches found for shader \'" << shaderName << "\'" << std::endl;
    }

    return validResult;
}

std::filesystem::path Plexi::Shaders::locateShader(const string &shaderName, Plexi::Shaders::ShaderLanguage shaderType) {

    return locateShader(DEFAULT_SHADER_PATH, shaderName, shaderType);
}

bool Plexi::Shaders::ShaderCreateInfo::isComplete(){
    //GLSL
    if(shaderLanguage == UNKNOWN){
        std::cout << "Unknown Shader type." << std::endl;
        return false;
    } else if (shaderLanguage == GLSL){
        if(glslFragmentCode != nullptr && glslVertexCode != nullptr){
            return true;
        }
        std::cerr << "GLSL Shader is not complete. Missing GLSL shader data." << std::endl;
        return false;
    } else if(shaderLanguage == SPIRV){
        if(spirvFragmentSize != 0 && spirvVertexSize != 0 && spirvFragmentCode != nullptr && spirvVertexCode == nullptr){
            return true;
        }
        std::cerr << "SPIR-V shader is not complete. Missing SPIR-V shader data." << std::endl;
        return false;
    }

    std::cerr << "Unrecognised shader type." << std::endl;
    return false;
}


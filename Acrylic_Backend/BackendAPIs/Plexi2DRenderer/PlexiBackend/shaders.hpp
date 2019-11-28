#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <glad/glad.h>
#include <string>
#include <memory>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>

typedef std::string string;
namespace Plexi::Shaders {
    enum DataType {//Data types that correspond to those inside of the shader NOTE: vecs are floats
        None = 0,
        Float, Float2, Float3, Float4,
        Int, Int2, Int3, Int4,
        Bool,
        Mat3, Mat4
    };

    //OpenGL specif - Might want to move in to OpenGL
    //Converts Plexi Data types to Open GL data types
    static GLenum convertDataTypeToGLSLBaseType(const DataType& dataType);

    //Gets the size of the data type as it is in most shading languages
    static uint32_t getDataTypeSize(const DataType& dataType);

    //Gets number of elements represented by each data type eg: float4 has four elements
    static uint32_t getDataTypeCount(const DataType& dataType);

    enum ShaderLanguage {
        UNKNOWN = 0,
        GLSL,
        SPIRV,
    };

    struct ShaderCreateInfo {
        string shaderName;
        ShaderLanguage shaderLanguage;
        std::shared_ptr<string> glslVertexCode;
        std::shared_ptr<string> glslFragmentCode;
        std::shared_ptr<uint32_t > spirvVertexCode;
        std::shared_ptr<uint32_t > spirvFragmentCode;
        size_t spirvVertexSize;
        size_t spirvFragmentSize;

        ShaderCreateInfo(string name, ShaderLanguage language) : shaderName(std::move(name)), shaderLanguage(language) {
            spirvVertexSize = 0;
            spirvFragmentSize = 0;
        }
        //Simple function to check if the required shader data is set
        bool isComplete();
    };

    static std::map<Plexi::Shaders::ShaderLanguage, std::vector<std::string>> RECOGNISED_EXTENSIONS = {
            {GLSL, {".glsl.vert", ".glsl.frag", ".glsl"}},
            {SPIRV, {".spv.vert", ".spv.frag", ".spv"}}
    };

    const std::filesystem::path DEFAULT_SHADER_PATH("./plexi_shaders/");

    static string loadGLSLShaderFromFile(const std::filesystem::path& shaderPath);

    static uint32_t* loadSPIRVShaderFromFile(const std::filesystem::path& shaderPath);

    static std::filesystem::path locateShader(const std::filesystem::path& pathToSearch, const string& shaderName, ShaderLanguage shaderType);

    static std::filesystem::path locateShader(const string& shaderName, ShaderLanguage shaderType);

    //TODO shader conversions with shader c


}
#endif //SHADERS_HPP
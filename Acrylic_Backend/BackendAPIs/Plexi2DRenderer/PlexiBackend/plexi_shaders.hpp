#ifndef PLEXI_SHADERS_HPP
#define PLEXI_SHADERS_HPP

#include <glad/glad.h>
#include <string>
#include <memory>
#include <iostream>
#include <filesystem>
#include <map>
#include <vector>
#include <fstream>
#include <ths/log.hpp>

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
    GLenum convertDataTypeToGLSLBaseType(const DataType& dataType);

    //Gets the size of the data type as it is in most shading languages
    uint32_t getDataTypeSize(const DataType& dataType);

    //Gets number of elements represented by each data type eg: float4 has four elements
    uint32_t getDataTypeCount(const DataType& dataType);

    enum ShaderLanguage {
        UNKNOWN = 0,
        GLSL,
        SPIRV,
    };

    struct ShaderCreateInfo {
        std::string shaderName = "";
        ShaderLanguage shaderLanguage = UNKNOWN;
        std::string glslVertexCode = "";
        std::string glslFragmentCode = "";
        std::shared_ptr<uint32_t > spirvVertexCode;
        std::shared_ptr<uint32_t > spirvFragmentCode;
        size_t spirvVertexSize = 0;
        size_t spirvFragmentSize = 0;

//        ShaderCreateInfo(std::string name, ShaderLanguage language) :
//        shaderName(std::move(name)), shaderLanguage(language), glslVertexCode(""), glslFragmentCode("")
//        {
//            spirvVertexSize = 0;
//            spirvFragmentSize = 0;
//        }
        //Simple function to check if the required shader data is set
        bool isComplete() const;
    };


    std::string loadGLSLShaderFromFile(const std::filesystem::path& shaderPath);

    uint32_t* loadSPIRVShaderFromFile(const std::filesystem::path& shaderPath);

    std::filesystem::path locateShader(const std::filesystem::path& pathToSearch, const std::string& shaderName, ShaderLanguage shaderType);

    std::filesystem::path locateShader(const std::string& shaderName, ShaderLanguage shaderType);

    //TODO shader conversions with shader c


}
#endif //PLEXI_SHADERS_HPP
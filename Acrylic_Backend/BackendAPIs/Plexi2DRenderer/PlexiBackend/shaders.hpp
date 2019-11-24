#ifndef SHADERS_HPP
#define SHADERS_HPP

#include <shaderc/shaderc.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

typedef std::string string;
struct Shader {
    string name = "Plexi2D Unloaded Shader";
    shaderc_shader_kind shaderType = shaderc_glsl_infer_from_source;
    std::vector<uint32_t> code = {};
};

namespace PlexiShaders {
    const string DEFAULT_SHADER_PATH = "./plexi_shaders/";
    
    Shader compileShaderFromString(string shaderName, string code, bool optimizeOutput);

    Shader compileShaderFromFile(string shaderName, bool optimizeOutput, bool deleteSrc);

    void outputShader(const Shader& shader);

    Shader loadShader(string shaderName);

    //Look for .frag.spv .vert.spv and .spv if found then load them
    bool checkForPrecompiledShaders(string shaderName);

}



#endif //SHADERS_HPP
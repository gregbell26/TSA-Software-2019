#ifndef SHADERS_HPP
#define SHADERS_HPP

//#include <shaderc/shaderc.hpp>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>
#include <array>

typedef std::string string;
namespace Plexi {
    struct Shader {
        string name = "Plexi2D Unloaded Shader";
        int shaderType = 0;
        const uint32_t *code = nullptr;
        size_t codeSize = 0;
    };

    namespace Shaders {

#ifndef PLEXI_LIBRARY_ACTIVE
        static const string DEFAULT_SHADER_PATH = "./plexi_shaders/";
        static const string DEFAULT_COMPILED_EXTENSION = ".spv";

        static const std::array<string, 3> RECOGNIZED_COMPILED_EXTENSIONS = {
                ".spv", ".frag.spv", ".vert.spv"
        };
#endif //PLEXI_LIBRARY_ACTIVE

        Shader compileShaderFromString(const string &shaderName, const string &code, bool optimizeOutput);

        Shader compileShaderFromFile(const string &shaderName, bool optimizeOutput, bool deleteSrc);

        void outputShader(const Shader &shader);

        Shader loadShader(const std::filesystem::path &shaderPath);

        Shader loadShader(const string &shaderName);

        //Look for .frag.spv .vert.spv and .spv if found then load them
        bool checkForPrecompiledShaders(const string &shaderName, Shader &outputShader);
    }


}
#endif //SHADERS_HPP
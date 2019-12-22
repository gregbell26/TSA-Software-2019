#include "./../plexiShaders.hpp"
#include "./../plexiBuffer.hpp"
#include "./../plexiHelper.hpp"

#include "OpenGLMain.hpp"

bool OpenGL::createShaders(const std::string& vertexSource, const std::string& fragmentSource, const std::string& shaderProgramName, pipelineComponentMap& pipelineMap) {
    // Create an empty vertex shader handle
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    auto  *source = (const GLchar *)vertexSource.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    GLint isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);

    if(isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.
        std::cerr << "OpenGL Shader Compilation Error: " << infoLog.data() << std::endl;

        // In this simple program, we'll just leave
        return false;
    }

    // Create an empty fragment shader handle
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = (const GLchar *)fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (isCompiled == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

        // We don't need the shader anymore.
        glDeleteShader(fragmentShader);
        // Either of them. Don't leak shaders.
        glDeleteShader(vertexShader);

        // Use the infoLog as you see fit.

        std::cerr << "OpenGL Shader compilation error " << infoLog.data() << std::endl;
        // In this simple program, we'll just leave
        return false;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE)
    {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        // Use the infoLog as you see fit.
        std::cerr << "OpenGL Shader link error: " << infoLog.data() << std::endl;
        // In this simple program, we'll just leave
        return false;
    }

    pipelineMap[SHADER_PROGRAM] = program;

    // Always detach shaders after a successful link.
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);


    return true;
}

void OpenGL::setInt(const std::string &pipelineName, const std::string &uniformName, const int &newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniform1i(uniformLocation, newValue);
}

void OpenGL::setFloat(const std::string& pipelineName, const std::string& uniformName, const float& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniform1f(uniformLocation, newValue);
}

void OpenGL::setFloat2(const std::string& pipelineName, const std::string& uniformName, const glm::vec2& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniform2f(uniformLocation, newValue.x, newValue.y);
}

void OpenGL::setFloat3(const std::string& pipelineName, const std::string& uniformName, const glm::vec3& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniform3f(uniformLocation, newValue.x, newValue.y, newValue.z);
}

void OpenGL::setFloat4(const std::string& pipelineName, const std::string& uniformName, const glm::vec4& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniform4f(uniformLocation, newValue.x, newValue.y, newValue.z, newValue.w);
}

void OpenGL::setMat3(const std::string& pipelineName, const std::string& uniformName, const glm::mat3& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniformMatrix3fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(newValue));
}

void OpenGL::setMat4(const std::string& pipelineName, const std::string& uniformName, const glm::mat4& newValue) {
    GLint uniformLocation = glGetUniformLocation(activePipelines[pipelineName][SHADER_PROGRAM], uniformName.c_str());
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(newValue));
}


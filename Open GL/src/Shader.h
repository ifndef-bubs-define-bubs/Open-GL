#pragma once

#include <vector>
#include <unordered_map>

class ShaderProgramSource {
public:
    std::string VertexShader;
    std::string FragmentShader;


};

class Shader {


private:
    std::string m_FilePath;
    unsigned int m_RendererID;
    std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filename);
    ~Shader();

    void Bind() const;
    void Unbind() const;


    // we also want to be able to set uniforms with this
    void SetUniform1i(const std::string& name, int value); // for textures ( I think )
    void SetUniformMat4f(const std::string& name, int number_of_matricies, unsigned int transpose, const float* matrix);
    void SetUniform1f(const std::string& name, float value);
    void SetUniform4f(const std::string& name, float v0, float v1, float f2, float f3);

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);

};
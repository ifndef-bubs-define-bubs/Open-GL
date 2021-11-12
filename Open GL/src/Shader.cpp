
#include "Shader.h"
#include "Renderer.h"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <string>



;  // should this not be in the header ?

Shader::Shader(const std::string& filepath)
:m_FilePath(filepath)// we save the filepath to m_filepath for debugging purposes
, m_RendererID(0)
{

    ScanForErrors(ShaderProgramSource source = ParseShader(filepath));
    /* std::cout << "VERTEX" << std::endl;
     std::cout << source.VertexShader << std::endl;
     std::cout << "FRAGMENT" << std::endl;
     std::cout << source.FragmentShader << std::endl; */

    m_RendererID = CreateShader(source.VertexShader, source.FragmentShader);
    
  // that renderer id is the id generated from the program being created 
}

Shader::~Shader()
{

    ScanForErrors(glDeleteProgram(m_RendererID));

}


// USER CALLED FUNCTIONS
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{

    ScanForErrors(glUniform4f(GetUniformLocation(name), v0,  v1, v2, v3));
}

void Shader::SetUniform1f(const std::string& name, float value)
{

    ScanForErrors(glUniform1f(GetUniformLocation(name),value));
}

void Shader::SetUniform1i(const std::string& name, int value)
{

    ScanForErrors(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniformMat4f(const std::string& name, int number_of_matricies, unsigned int transpose, const float* matrix)
{
    ScanForErrors(glUniformMatrix4fv(GetUniformLocation(name), number_of_matricies, transpose, matrix));
}

void Shader::Bind() const
{

    ScanForErrors(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
    ScanForErrors(glUseProgram(0));

}


//AUTOMATICALLY CALLED FUNCTIONS
ShaderProgramSource Shader::ParseShader(const std::string& filepath) {

    enum class ShaderType {

        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::ifstream stream(filepath);
    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (std::getline(stream, line)) {   // while there are still lines remaining 

        if (line.find("#shader") != std::string::npos) { //npos is what .find() returns when it has not found anything. It is a static const

            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    // below, we in a way, bind our shaders to the program we createed

    ScanForErrors(glAttachShader(program, vs));
    ScanForErrors(glAttachShader(program, fs));
    ScanForErrors(glLinkProgram(program));
    ScanForErrors(glValidateProgram(program));

    // code below deletes intermediate object files from Microsoft's compiler that aren't useful, since the shaders have already been linked to the program 


    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);       //GL_VERTEX_SHADER is actually equal to an usigned int 
    const char* src = source.c_str();                         // opengl wants a raw string, and we give that to it by using c.str() which points to the first element of source
    ScanForErrors(glShaderSource(id, 1, &src, nullptr));                     // nullptr basically is null terminated (ends with a zero), which helps opengl know where the string ends, instead of giving it the length manually 
    ScanForErrors(glCompileShader(id));

    // error handling, in case compileShader f's up 

    // we are queerying (however you spell it) glGetShader 

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);            // iv at the end of the glGetShader means the function wants an integer, and the v means it wants a vector/array, which basically means a pointer 

    if (result == GL_FALSE) {

        // you can see that depending on the second parameter, you can retrieve different pieces of information from the getShadreriv

        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);       // we get the length of the message that the function has to give us
        char* message = (char*)alloca(length * sizeof(char)); // we use a char array here because it has a quicker generation time than an ordinary string. Alloca is the same as new, except, it puts makes space available on the stack. Remember to always cast alloca back to whatever you need it to be
        glGetShaderInfoLog(id, length, &length, message);     // we give it back the length, so it knows how long it is

        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader !" << std::endl;
        std::cout << message << std::endl;

        glDeleteShader(id);

        return 0;
    }


    return id;                                                // we return id, and don't waste time, because if source has somehow gone out of scope, then we're fucked, because, src will point to rubbish memory, so we capture everything we need in the lvalue id

}

 int Shader::GetUniformLocation(const std::string& name)
{
    //  WE USED THE HASH MAP TO REDUCE THE NUMBER OF TIMES WE CALL GET UNIFORM LOCATION, AS IT TAKES SOME TIME  

    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end()) // if we have found name in our hash map do this                                                                   // if not, then continue with the code below
        return m_UniformLocationCache[name];
    
    ScanForErrors(int location = glGetUniformLocation(m_RendererID, name.c_str()));

    if (location == -1)
        std::cout << "Warning: Uniform " << name << " is not found..." << std::endl;


    m_UniformLocationCache[name] = location;
    return location;
        //if you've read my notes in the shader file, 
        //you can see that we made a u_colour vairable.
        //however, opengl needs to kinda know where to get this u_colour from, so we use the above function, 
        //giving it the shader id and the name of the variable.
        // NOTE : MUST SPELL THE UNIFORM VARIABLE CORRECTLY
}
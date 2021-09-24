#pragma once

std::string get_file_contents(const char* filename);

struct shaderInput {
	std::string name;
	std::string vert;
	std::string frag;
};

class Shader
{
public:
	// Reference ID of the Shader Program
	GLuint ID;
	// Constructor that build the Shader Program from 2 different shaders
	Shader(const char* vertexFile, const char* fragmentFile);

	// Activates the Shader Program
	void Activate();
	// Deletes the Shader Program
	void Delete();
private:
	// Checks if the different Shaders have compiled properly
	void compileErrors(unsigned int shader, const char* type);
};

struct shaderStruct {
	std::string name;
	Shader program;
};

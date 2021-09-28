#pragma once

// Structure to standardize the vertices used in the meshes
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec3 color;
	glm::vec2 texUV;
};

class VBO
{
public:
	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(std::vector<Vertex>& vertices);
	VBO(std::vector<glm::mat4>& mat4s);
	~VBO();

	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();

private:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;
};

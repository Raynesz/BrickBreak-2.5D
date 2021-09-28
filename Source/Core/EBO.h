#pragma once

class EBO
{
public:
	// Constructor that generates a Elements Buffer Object and links it to indices
	EBO(std::vector<GLuint>& indices);
	~EBO();

	// Binds the EBO
	void Bind();
	// Unbinds the EBO
	void Unbind();

private:
	// ID reference of Elements Buffer Object
	GLuint ID;
};

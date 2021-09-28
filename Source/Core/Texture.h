#pragma once

class Texture
{
public:
	const char* type;

	Texture(const char* image, const char* texType, GLuint slot);

	// Assigns a texture unit to a texture
	void texUnit(Shader& shader, const char* uniform, GLuint unit);
	// Binds a texture
	void Bind();
	// Deletes a texture
	void Delete();

private:
	GLuint ID;
	GLuint unit;

	// Unbinds a texture
	void Unbind();
};

#include "Game.h"

Wall::Wall(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale, float length, float width)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	Wall::length = length;
	Wall::width = width;

	this->Scale(width, length, this->scale.z);
}

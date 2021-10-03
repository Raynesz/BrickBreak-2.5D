#include "Game.h"

Laser::Laser(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	
}

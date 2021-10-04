#include "Game.h"

Laser::Laser(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	destroyed = true;
}

void Laser::Update(glm::vec3 barPosition) {
	position = glm::vec3(barPosition.x, barPosition.y + scale.y, barPosition.z);
	destroyed = charges > 0 ? false : true;
}

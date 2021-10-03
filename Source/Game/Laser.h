#pragma once

class Laser : public Entity {
public:
	int charges = 0;

	Laser(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale);
};

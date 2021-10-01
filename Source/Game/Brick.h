#pragma once

class Brick : public Entity {
public:
	std::string type;
	int lives;

	Brick(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale);
};

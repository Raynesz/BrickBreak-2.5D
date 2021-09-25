#pragma once

class Wall : public Entity {
public:
	float length = 1.0f;
	float width = 1.0f;

	Wall(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale, float length, float width);
};

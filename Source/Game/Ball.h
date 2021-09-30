#pragma once

class Ball : public Entity {
public:
	float radius = 1.0f;

	Ball(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale, float radius);
	void Update(float);
};

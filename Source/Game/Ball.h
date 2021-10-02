#pragma once

class Ball : public Entity {
public:
	float radius = 1.0f;
	float speedModified = 0.0;
	const float normal = 9.0f;
	const float fast = 15.0f;
	const float slow = 3.0f;

	Ball(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale, float radius);
	void Update(float);
	void adjustSpeed();
};

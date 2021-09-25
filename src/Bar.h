#pragma once

struct moveControl {
	bool forward = false, back = false, right = false, left = false;
};

class Bar : public Entity {
public:
	float length = 1.0f;
	moveControl move;

	Bar(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale, float length);

	void Update(float, moveControl);
};

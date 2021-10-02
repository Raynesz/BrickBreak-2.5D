#pragma once

struct moveControl {
	bool forward = false, back = false, right = false, left = false;
};

struct barBorder {
	float left;
	float right;
};

class Bar : public Entity {
public:
	float length = 1.0f;
	float height = 0.5f;
	barBorder border;
	moveControl move;
	double shrinkDuration = 0.0;

	Bar(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale, float length, float height, float wallXoffset, float wallWidth);

	void Update(float);
	void setLength(float newLength);
};

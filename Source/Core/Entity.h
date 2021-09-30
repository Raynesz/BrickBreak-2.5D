#pragma once

class Entity {
public:
	bool destroyed = false;
	std::string name;
	int modelIndex;
	int shaderIndex;
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 0.0f;

	Entity(std::string, std::string, std::string, std::vector<modelStruct>&, std::vector<shaderStruct>&, glm::vec3, glm::vec3);

	void Translate(float x, float y, float z);
	void Rotate(double x, double y, double z, double a);
	void Scale(float x, float y, float z);
	void SetModel(std::vector<modelStruct>&, std::string);
};

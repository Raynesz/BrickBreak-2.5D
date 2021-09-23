#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include "Shader.h"
#include "Model.h"

class Entity {
public:
	std::string name;
	bool isPlayer;
	int modelIndex;
	int shaderIndex;
	glm::vec3 position;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 direction = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 8.0f;

	Entity(std::string, int, int, glm::vec3, glm::vec3);

	void update(float);
	void update(float, moveControl);
	void Translate(float x, float y, float z);
	void Rotate(double x, double y, double z, double a);
	void Scale(float x, float y, float z);
};

#endif

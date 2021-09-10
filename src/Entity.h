#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <string>
#include "Shader.h"
#include "Model.h"

struct moveControl {
	bool forward = false, back = false, right = false, left = false;
};

class Entity {
public:
	std::string name;
	bool isPlayer;
	int modelIndex;
	int shaderIndex;
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 orientation = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	float speed = 5.0f;

	Entity(std::string, bool, int, int);

	void update(float);
	void update(float, moveControl);
	void moveTo(glm::vec3);
	void Rotate(double x, double y, double z, double a);
	void Scale(float x, float y, float z);
};

#endif

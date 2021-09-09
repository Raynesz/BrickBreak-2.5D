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
	glm::vec3 speed;

	Entity(std::string, bool, int, int);

	void update();
	void update(moveControl);
	void moveTo(glm::vec3);
	void Rotate(double x, double y, double z, double a);
	void Scale(float x, float y, float z);
};

#endif

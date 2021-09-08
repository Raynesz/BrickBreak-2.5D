#ifndef ENTITY_CLASS_H
#define ENTITY_CLASS_H

#include <string>
#include "Shader.h"
#include "Model.h"

class Entity {
public:
	std::string name;
	int modelIndex;
	int shaderIndex;
	glm::vec3 translation;
	glm::quat rotation;
	glm::vec3 scale;
	glm::vec3 speed;

	Entity(std::string, int, int);

	void update();
	void moveTo(glm::vec3);
};

#endif
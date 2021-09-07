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

	Entity(std::string, int, int);

	void update(glm::vec3, glm::quat, glm::vec3);

	//void Draw(Camera& camera);

};

#endif
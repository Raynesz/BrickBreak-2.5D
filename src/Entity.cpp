#include "Entity.h"

Entity::Entity(std::string newName, int newModelIndex, int newShaderIndex) {
	name = newName;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	speed = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Entity::update() {
	translation = glm::vec3(translation.x + speed.x, translation.y + speed.y, translation.z + speed.z);
}

void Entity::moveTo(glm::vec3 location) {
	translation = location;
}
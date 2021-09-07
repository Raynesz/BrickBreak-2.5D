#include "Entity.h"

Entity::Entity(std::string newName, int newModelIndex, int newShaderIndex) {
	name = newName;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	translation = glm::vec3(0.0f, 30.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

//void Entity::Draw(Camera& camera) {
//	model.Draw(shader, camera, translation, rotation, scale);
//}
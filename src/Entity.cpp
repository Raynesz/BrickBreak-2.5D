#include "Entity.h"

Entity::Entity(std::string newName, int newModelIndex, int newShaderIndex, glm::vec3 translation, glm::vec3 scale) {
	name = newName;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	position = translation;
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	Entity::scale = scale;
}

void Entity::update(float deltaTime) {

}

void Entity::update() {

}

void Entity::Translate(float x, float y, float z) {
	position = glm::vec3(x, y, z);
}

void Entity::Rotate(double x, double y, double z, double a) {
	// Here we calculate the sin( theta / 2) once for optimization
	double factor = sin(a / 2.0f);

	// Calculate the x, y and z of the quaternion
	double xx = x * factor;
	double yy = y * factor;
	double zz = z * factor;

	// Calcualte the w value by cos( theta / 2 )
	double w = cos(a / 2.0);

	rotation *= glm::quat(w, xx, yy, zz);
}

void Entity::Scale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}
#include "Entity.h"

Entity::Entity(std::string newName, bool isPlayer, int newModelIndex, int newShaderIndex) {
	name = newName;
	Entity::isPlayer = isPlayer;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Entity::update(float deltaTime) {

}

void Entity::update(float deltaTime, moveControl mC) {
	if (mC.forward)
		position += (deltaTime * speed) * direction;
	if (mC.back)
		position += (deltaTime * speed) * -direction;
	if (!mC.forward && !mC.back)
		position += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
	if (mC.left)
		position += (deltaTime * speed) * -glm::normalize(glm::cross(direction, up));
	if (mC.right)
		position += (deltaTime * speed) * glm::normalize(glm::cross(direction, up));
	if (!mC.left && !mC.right)
		position += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
}

void Entity::moveTo(glm::vec3 location) {
	position = location;
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
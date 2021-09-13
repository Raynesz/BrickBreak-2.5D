#include "Entity.h"

Entity::Entity(std::string newName, bool isPlayer, int newModelIndex, int newShaderIndex) {
	name = newName;
	Entity::isPlayer = isPlayer;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Entity::update(float deltaTime) {

}

void Entity::update(float deltaTime, moveControl mC) {
	glm::vec3 direction;
	if (mC.forward)
		translation += (deltaTime * speed) * orientation;
	if (mC.back)
		translation += (deltaTime * speed) * -orientation;
	if (!mC.forward && !mC.back)
		translation += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
	if (mC.left)
		translation += (deltaTime * speed) * -glm::normalize(glm::cross(orientation, up));
	if (mC.right)
		translation += (deltaTime * speed) * glm::normalize(glm::cross(orientation, up));
	if (!mC.left && !mC.right)
		translation += (deltaTime * speed) * glm::vec3(0.0f, 0.0f, 0.0f);
}

void Entity::moveTo(glm::vec3 location) {
	translation = location;
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
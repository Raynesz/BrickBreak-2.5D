#include "Entity.h"

Entity::Entity(std::string newName, bool isPlayer, int newModelIndex, int newShaderIndex) {
	name = newName;
	Entity::isPlayer = isPlayer;
	modelIndex = newModelIndex;
	shaderIndex = newShaderIndex;

	translation = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);

	speed = glm::vec3(0.0f, 0.0f, 0.0f);
}

void Entity::update() {

}

void Entity::update(moveControl mC) {
	if (mC.forward)
		speed.x = 0.02f;
	if (mC.back)
		speed.x = -0.02f;
	if (!mC.forward && !mC.back)
		speed.x = 0.0f;
	if (mC.left)
		speed.z = -0.02f;
	if (mC.right)
		speed.z = 0.02f;
	if (!mC.left && !mC.right)
		speed.z = 0.0f;
	translation = glm::vec3(translation.x + speed.x, translation.y + speed.y, translation.z + speed.z);
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

	rotation = rotation * glm::quat(w, xx, yy, zz);
}

void Entity::Scale(float x, float y, float z) {
	scale = glm::vec3(x, y, z);
}
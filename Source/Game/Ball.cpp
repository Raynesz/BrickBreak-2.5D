#include "Game.h"

Ball::Ball(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale, float radius)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	Ball::radius = radius;
	this->Scale(radius, radius, radius);
	direction = glm::rotate(up, glm::radians(random(-50.0f, 50.0f)), glm::vec3(0, 0, 1));
}

void Ball::Update(float deltaTime) {
	if (speedModified > 0.0) speedModified -= deltaTime;
	else speed = normal;
	position += (deltaTime * speed) * direction;
}

void Ball::adjustSpeed() {
	if (random(0, 100) >= 50)
		speed = slow;
		speedModified += 2.0;
	else {
		speed = fast;
		speedModified += 10.0;
	}
}

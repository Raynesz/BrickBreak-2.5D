#include "Viewer.h"

Entity::Entity(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models,
	std::vector<shaderStruct>& shaders, glm::vec3 translation, glm::vec3 scale) {
	Entity::name = name;
	int modelIndex = 0, shaderIndex = 0;
	for (int i = 0; i < models.size(); i++) {
		if (modelID == models[i].name) {
			modelIndex = i;
		}
	}

	for (int i = 0; i < shaders.size(); i++) {
		if (shaderID == shaders[i].name) {
			shaderIndex = i;
		}
	}
	Entity::modelIndex = modelIndex;
	Entity::shaderIndex = shaderIndex;

	position = translation;
	rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
	Entity::scale = scale;
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

void Entity::SetModel(std::vector<modelStruct>& models, std::string newModel) {
	for (int i = 0; i < models.size(); i++) {
		if (newModel == models[i].name) modelIndex = i;
	}
}

void Entity::SetColor(glm::vec4 newColor) {
	Entity::baseColor = newColor;
}

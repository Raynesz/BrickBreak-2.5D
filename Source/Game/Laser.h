#pragma once

enum LaserState {Inactive, ReadyToFire, Fired};

class Laser : public Entity {
public:
	int state = Inactive;
	int prevState = Inactive;
	int charges = 0;
	int show = 0;

	Laser(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
		glm::vec3 translation, glm::vec3 scale);
	void Update(glm::vec3, float dt);
};

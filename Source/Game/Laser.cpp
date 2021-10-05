#include "Game.h"

Laser::Laser(std::string name, std::string modelID, std::string shaderID, std::vector<modelStruct>& models, std::vector<shaderStruct>& shaders,
	glm::vec3 translation, glm::vec3 scale)
	: Entity(name, modelID, shaderID, models, shaders, translation, scale)
{
	destroyed = true;
}

void Laser::Update(glm::vec3 barPosition, float dt) {
	position = glm::vec3(barPosition.x, barPosition.y + scale.y, barPosition.z);

	if (state == Fired) {
		SetColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)); // Red
		if (prevState == ReadyToFire) {
			show = 20;
		}
		else if (prevState == Fired) {
			show -= dt;
		}
		else if (prevState == Inactive) {
			show = 0;
		}
		if (show <= 0) {
			state = (charges > 0) ? ReadyToFire : Inactive;
		}
		prevState = Fired;
	}
	else if (state == ReadyToFire) {
		SetColor(glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)); // Yellow
		if (prevState == Fired || prevState == Inactive) {
			show = 10;
		}
		else if (prevState == ReadyToFire) {
			show -= dt;
		}
		if (show <= 0) {
			show = 10;
		}
		prevState = ReadyToFire;
	}
	else if (state == Inactive) {
		state = (charges > 0) ? ReadyToFire : Inactive;
		show = 0;
		prevState = Inactive;
	}

	destroyed = (show > 5) ? false: true;
}

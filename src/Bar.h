#ifndef BAR_H
#define BAR_H

struct moveControl {
	bool forward = false, back = false, right = false, left = false;
};

class Bar : public Entity {
public:
	float width = 1.0f;
	moveControl move;

	//Bar(std::string, std::string, std::string, glm::vec3, glm::vec3, float);

	void Update(float, moveControl);
};

#endif

#ifndef VIEWER_CLASS_H
#define VIEWER_CLASS_H

#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Skybox.h"
#include "Entity.h"
#include <math.h>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "constants.h"
#include "util.h"

class Viewer {
public:
	std::string windowName;
	unsigned int width;
	unsigned int height;

	GLFWwindow* window;
	// Creates camera object
	Camera camera;
	Skybox skybox;

	std::vector<shaderStruct> shaders = {};
	std::vector<modelStruct> models = {};
	std::vector<Entity> entities = {};

	moveControl playerMove;

	// Variables to create periodic event for FPS displaying
	double previousTime = 0.0;
	double currentTime = 0.0;
	double dt = 0.0;

	Viewer(std::string);
	~Viewer();

	void LoadModel(std::vector<std::string>& modelNames);
	void loadShader(std::vector<shaderInput>& shaderInputData);
	void useSkybox(std::string skyboxName);
	void addEntity(std::string entityName, bool isPlayer, std::string modelID, std::string shaderID);
	int g(std::string);
	void drawSkybox();
	void drawEntities();
	void updateEntities();
	void Inputs();
};

#endif

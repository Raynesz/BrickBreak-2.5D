#ifndef VIEWER_H
#define VIEWER_H

#include <math.h>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include "constants.h"
#include "util.h"
#include "Camera.h"
#include "Model.h"
#include "Shader.h"
#include "Skybox.h"
#include "Entity.h"

class Viewer {
public:
	std::string windowName;
	unsigned int width;
	unsigned int height;

	GLFWwindow* window;
	// Creates camera object
	Camera camera;
	Skybox skybox;

	bool showAbout = false;
	bool showMetrics = true;
	bool showControls = false;

	std::vector<shaderStruct> shaders = {};
	std::vector<modelStruct> models = {};
	std::vector<Entity> entities = {};

	moveControl playerMove;

	// Variables to create periodic event for FPS displaying
	double previousTime = glfwGetTime();
	double currentTime = 0.0;
	double dt = 0.01666f;

	Viewer(std::string);
	~Viewer();

	void loadModels(std::vector<std::string>&);
	void loadShaders(std::vector<shaderInput>&);
	void loadSkyboxes(std::vector<std::string>&);
	void useSkybox(std::string skyboxName);
	void addEntity(std::string entityName, bool isPlayer, std::string modelID, std::string shaderID);
	int g(std::string);
	void drawSkybox();
	void drawEntities();
	void updateEntities();
	void Inputs();
	void FpsCounter();
};

#endif

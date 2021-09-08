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

	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	Viewer(std::string, int, int);
	~Viewer();

	void LoadModel(std::vector<std::string>& modelNames);
	void loadShader(std::vector<shaderInput>& shaderInputData);
	void useSkybox(std::string skyboxName);
	void addEntity(std::string, std::string, std::string);
	void drawSkybox();
	void drawEntities();
	void updateEntities();
	void Inputs();
};

#endif

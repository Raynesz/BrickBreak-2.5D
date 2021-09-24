#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <cerrno>
#include <math.h>
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <json/json.h>

#include "constants.h"
#include "util.h"
#include "physics.h"
#include "ui.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"
#include "Shader.h"
#include "Texture.h"
#include "Camera.h"
#include "Mesh.h"
#include "Model.h"
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

	// Variables to create periodic event for FPS displaying
	double previousTime = glfwGetTime();
	double currentTime = 0.0;
	double dt = 0.01666f;

	Viewer(std::string);
	~Viewer();

	void loadModels(std::vector<std::string>&);
	void loadShaders(std::vector<shaderInput>&);
	void loadSkyboxes(std::vector<std::string>&);
	void useSkybox(std::string);
	int get(std::string);
	void drawSkybox();
	void drawEntities();
	void Inputs();
	void FpsCounter();
};

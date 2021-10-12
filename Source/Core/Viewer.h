#pragma once

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
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
#include <csv.h>
#include "soLoud/soloud.h"
#include "soLoud/soloud_wav.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "constants.h"
#include "util.h"
#include "physics.h"
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
#include "ui.h"

struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

class Viewer {
public:
	unsigned int width;
	unsigned int height;

	GLFWwindow* window;
	SoLoud::Soloud& soloud;

	std::map<GLchar, Character> textCharacters;
	unsigned int textVAO, textVBO;

	double dt = 0.01666f;

	std::vector<shaderStruct> shaders = {};
	std::vector<modelStruct> models = {};

	Viewer(std::string, SoLoud::Soloud&);
	~Viewer();

	void loadModels(std::vector<std::string>&);
	void loadShaders(std::vector<shaderInput>&);
	void loadSkyboxes(std::vector<std::string>&);
	void useSkybox(std::string skyboxName);
	void drawSkybox(Camera&);
	void drawEntities(Camera&, std::vector<Entity*>);
	void Inputs();
	void FpsCounter();
	int TextInit();
	void RenderText(std::string text, float x, float y, float scale, glm::vec3 color);

private:
	std::string windowName;
	Skybox skybox;

	// Variables to create periodic event for FPS displaying
	double previousTime = glfwGetTime();
	double currentTime = 0.0;
};

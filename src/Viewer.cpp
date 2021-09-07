#include "Viewer.h"

Viewer::Viewer(std::string wN, int w, int h) : camera(w, h, glm::vec3(0.0f, 0.0f, 10.0f)) {
	try {
		windowName = wN;
		width = w;
		height = h;
		// Initialize GLFW
		glfwInit();

		// Tell GLFW what version of OpenGL we are using 
		// In this case we are using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
		window = glfwCreateWindow(width, height, "BrickBreak 2.5D", NULL, NULL);
		// Error check if the window fails to create
		if (window == NULL)
		{
			throw;
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, width, height);

		skybox.Initialize();

		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		// Enables Cull Facing
		glEnable(GL_CULL_FACE);
		// Keeps front faces
		glCullFace(GL_FRONT);
		// Uses counter clock-wise standard
		glFrontFace(GL_CCW);

		// Use this to disable VSync (not advized)
		//glfwSwapInterval(0);
	} catch(const std::exception& e) {
		std::cout << "Failed to create GLFW window"<< e.what() << std::endl;
		glfwTerminate();
	}
}

Viewer::~Viewer() {
	// Delete all the objects we've created
	for (int i = 0; i < shaders.size(); i++) {
		shaders[i].program.Delete();
	}
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Viewer::LoadModel(std::vector<std::string>& modelNames) {
	for (int i = 0; i < modelNames.size(); i++) {
		std::string modelPath = "res/models/" + modelNames[i] + "/scene.gltf";
		Model modelData(modelPath.c_str());
		models.push_back(modelStruct(modelNames[i], (modelPath.c_str())));
	}
}

void Viewer::loadShader(std::vector<shaderInput>& shaderInputData) {
	for (int i = 0; i < shaderInputData.size(); i++) {
		std::string shaderVertPath = "res/shaders/" + shaderInputData[i].vert + ".vert";
		std::string shaderFragPath = "res/shaders/" + shaderInputData[i].frag + ".frag";
		Shader shaderProgram(shaderVertPath.c_str(), shaderFragPath.c_str());
		shaders.push_back(shaderStruct(shaderInputData[i].name, shaderProgram));
	}

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);

	for (int i = 0; i < shaders.size(); i++) {
		if (shaders[i].name == "skybox") {
			shaders[i].program.Activate();
			glUniform1i(glGetUniformLocation(shaders[i].program.ID, "skybox"), 0);
		}
		else {
			shaders[i].program.Activate();
			glUniform4f(glGetUniformLocation(shaders[i].program.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
			glUniform3f(glGetUniformLocation(shaders[i].program.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		}
	}
}

void Viewer::useSkybox(std::string skyboxName) {
	skybox.useSkybox(skyboxName);
}

void Viewer::addEntity(std::string entityName, std::string modelID, std::string shaderID) {
	int modelIndex, shaderIndex;
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

	Entity newEnt(entityName, modelIndex, shaderIndex);
	entities.push_back(newEnt);
}

void Viewer::drawSkybox() {
	skybox.Draw(shaders[0].program, camera, width, height);
}

void Viewer::drawEntities() {
	for (int i = 0; i < entities.size(); i++) {
		models[entities[i].modelIndex].model.Draw(shaders[entities[i].shaderIndex].program, camera, entities[i].translation, entities[i].rotation, entities[i].scale);
	}
}

void Viewer::Inputs() {
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		useSkybox("skyfly");
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		useSkybox("space");
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		useSkybox("");
	}
}
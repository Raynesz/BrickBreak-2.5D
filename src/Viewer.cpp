#include "Viewer.h"

Viewer::Viewer(std::string windowName) {
	try {
		// Initialize GLFW
		glfwInit();

		// Using OpenGL 3.3
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		// Tell GLFW we are using the CORE profile
		// So that means we only have the modern functions
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		//glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		//glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
		glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

		glfwWindowHint(GLFW_SAMPLES, 4);

		Viewer::windowName = windowName;

		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		const GLFWvidmode* mode = glfwGetVideoMode(primary);

		width = mode->width;
		height = mode->height;
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(width, height, windowName.c_str(), NULL, NULL);

		// Error check if the window fails to create
		if (window == NULL)
		{
			std::cout << "here" << std::endl;
			throw;
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		GLFWimage images[1] = {};
		images[0].pixels = stbi_load("res/img/icon/wall_Icon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, width, height);

		camera.Initialize(width, height, glm::vec3(0.0f, 0.0f, 20.0f));

		skybox.Initialize();

		// Enables the Depth Buffer
		glEnable(GL_DEPTH_TEST);

		// Enables Cull Facing
		glEnable(GL_CULL_FACE);
		// Keeps front faces
		glCullFace(GL_FRONT);
		// Uses counter clock-wise standard
		glFrontFace(GL_CCW);

		glEnable(GL_MULTISAMPLE); // MSAA ON

		// 1: Vsync ON, 0: Uncapped frame rate
		glfwSwapInterval(1);
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

void Viewer::loadModels(std::vector<std::string>& modelNames) {
	for (int i = 0; i < modelNames.size(); i++) {
		std::string modelPath = "res/models/" + modelNames[i] + "/scene.gltf";
		Model modelData(modelPath.c_str());
		models.push_back(modelStruct(modelNames[i], modelData));
	}
}

void Viewer::loadShaders(std::vector<shaderInput>& shaderInputData) {
	for (int i = 0; i < shaderInputData.size(); i++) {
		std::string shaderVertPath = "res/shaders/" + shaderInputData[i].vert + ".vert";
		std::string shaderFragPath = "res/shaders/" + shaderInputData[i].frag + ".frag";
		Shader shaderProgram(shaderVertPath.c_str(), shaderFragPath.c_str());
		shaders.push_back(shaderStruct(shaderInputData[i].name, shaderProgram));
	}

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 0.0f, 0.0f);

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

void Viewer::loadSkyboxes(std::vector<std::string>& skyboxNames) {
	for (int i = 0; i < skyboxNames.size(); i++) skybox.loadSkybox(skyboxNames[i]);
}

void Viewer::useSkybox(std::string skyboxName) {
	skybox.useSkybox(skyboxName);
}

void Viewer::addEntity(std::string entityName, bool isPlayer, std::string modelID, std::string shaderID) {
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

	Entity newEnt(entityName, isPlayer, modelIndex, shaderIndex);
	entities.push_back(newEnt);
}

int Viewer::g(std::string entityName) {
	for (int i = 0; i < entities.size(); i++) {
		if (entityName == entities[i].name) return i;
	}
}

void Viewer::drawSkybox() {
	skybox.Draw(shaders[0].program, camera, width, height);
}

void Viewer::drawEntities() {
	for (int i = 0; i < entities.size(); i++) {
		models[entities[i].modelIndex].model.Draw(shaders[entities[i].shaderIndex].program, camera, entities[i].position, entities[i].rotation, entities[i].scale);
	}
}

void Viewer::updateEntities() {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i].isPlayer)
			entities[i].update(dt, playerMove);
		else
			entities[i].update(dt);
	}
}

void Viewer::Inputs() {
	// Handles key inputs
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)						//UP
	{
		//playerMove.forward = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		//playerMove.forward = false;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)					//DOWN
	{
		//playerMove.back = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		//playerMove.back = false;
	}

	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)						//UP
	{
		playerMove.back = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		playerMove.back = false;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)					//DOWN
	{
		playerMove.forward = true;
	}
	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		playerMove.forward = false;
	}

	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS)
	{
		useSkybox(NONE);
	}
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS)
	{
		useSkybox("skyfly");
	}
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS)
	{
		useSkybox("space");
	}
	if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS)
	{
		
	}
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		showAbout = true;
	}
}

void Viewer::FpsCounter() {
	currentTime = glfwGetTime();
	dt = currentTime - previousTime;

	/*
	// Creates new title
	std::string FPS = std::to_string(1.0/dt);
	std::string ms = std::to_string(dt);
	std::string newTitle = windowName + "   |   " + FPS + " FPS / " + ms + " ms";
	glfwSetWindowTitle(window, newTitle.c_str());
	*/

	previousTime = currentTime;
}

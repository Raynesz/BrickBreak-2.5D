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
			std::cout << "Window creation failed." << std::endl;
			throw;
		}

		// Introduce the window into the current context
		glfwMakeContextCurrent(window);

		GLFWimage images[1] = {};
		images[0].pixels = stbi_load("Resources/Icons/windowIcon.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
		glfwSetWindowIcon(window, 1, images);
		stbi_image_free(images[0].pixels);

		//Load GLAD so it configures OpenGL
		gladLoadGL();
		// Specify the viewport of OpenGL in the Window
		// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
		glViewport(0, 0, width, height);

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

		skybox.Initialize();
	} catch(const std::exception& e) {
		std::cout << "Failed to create GLFW window"<< e.what() << std::endl;
		glfwTerminate();
	}
}

Viewer::~Viewer() {
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
}

void Viewer::loadModels(std::vector<std::string>& modelNames) {
	for (int i = 0; i < modelNames.size(); i++) {
		std::string modelPath = "Resources/Models/" + modelNames[i] + "/scene.gltf";
		Model modelData(modelPath.c_str());
		models.push_back(modelStruct(modelNames[i], modelData));
	}
}

void Viewer::loadShaders(std::vector<shaderInput>& shaderInputData) {
	for (int i = 0; i < shaderInputData.size(); i++) {
		std::string shaderVertPath = "Resources/Shaders/" + shaderInputData[i].vert + ".vert";
		std::string shaderFragPath = "Resources/Shaders/" + shaderInputData[i].frag + ".frag";
		Shader shaderProgram(shaderVertPath.c_str(), shaderFragPath.c_str());
		shaders.push_back(shaderStruct(shaderInputData[i].name, shaderProgram));
	}

	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.0f, 5.0f, 35.0f);

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

void Viewer::drawSkybox(Camera& camera) {
	skybox.Draw(shaders[0].program, camera, width, height);
}

void Viewer::drawEntities(Camera& camera, std::vector<Entity*> entities) {
	for (int i = 0; i < entities.size(); i++) {
		if (!entities[i]->destroyed) models[entities[i]->modelIndex].model.Draw(shaders[entities[i]->shaderIndex].program,
			camera, entities[i]->position, entities[i]->rotation, entities[i]->scale);
	}
}

void Viewer::Inputs() {
	
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

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// Initializes matrices since otherwise they will be the null matrix
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	// Makes camera look in the right direction from the right position
	view = glm::lookAt(Position, Position + Orientation, Up);
	// Adds perspective to the scene
	projection = glm::perspective(glm::radians(FOVdeg), (float)width / height, nearPlane, farPlane);

	// Sets new camera matrix
	cameraMatrix = projection * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	// Exports camera matrix
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}

//TODO: Viewer responds to window resizing.
//Issue: Right cubemap texture is flipped after first render.

#include <iostream>
#include <string>
#include "Viewer.h"

void initializeResources(Viewer&);
void displayFPS(Viewer&);

int main() {
	Viewer viewer("BrickBreak 2.5D", 800, 800);
	initializeResources(viewer);

	viewer.useSkybox("skyfly");

	viewer.addEntity("airplane", "airplane", "default");
	viewer.addEntity("jupiter", "jupiter", "default");

	viewer.entities[0].update(glm::vec3(30.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));
	viewer.entities[1].update(glm::vec3(-30.0f, 0.0f, 0.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	for (int i = 0; i < viewer.entities.size(); i++) {
		std::cout << viewer.entities[i].name << std::endl;
	}

	// Main while loop
	while (!glfwWindowShouldClose(viewer.window))
	{
		displayFPS(viewer);

		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		viewer.Inputs();
		// Handles camera inputs (delete this if you have disabled VSync)
		viewer.camera.Inputs(viewer.window);
		// Updates and exports the camera matrix to the Vertex Shader
		viewer.camera.updateMatrix(45.0f, 0.1f, 1000.0f);

		viewer.drawEntities();
		viewer.drawSkybox();

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(viewer.window);
		// Take care of all GLFW events
		glfwPollEvents();
	}

	return 0;
}

void initializeResources(Viewer& viewer) {
	std::vector<std::string> models = {"airplane", "jupiter"};
	std::vector<shaderInput> shaders = { shaderInput("skybox", "skybox", "skybox"), shaderInput("default", "default", "default"), shaderInput("asteroid", "asteroid", "default")};

	viewer.LoadModel(models);
	viewer.loadShader(shaders);
}

void displayFPS(Viewer &viewer) {
	// Updates counter and times
	viewer.crntTime = glfwGetTime();
	viewer.timeDiff = viewer.crntTime - viewer.prevTime;
	viewer.counter++;

	if (viewer.timeDiff >= 1.0 / 30.0)
	{
		// Creates new title
		std::string FPS = std::to_string((1.0 / viewer.timeDiff) * viewer.counter);
		std::string ms = std::to_string((viewer.timeDiff / viewer.counter) * 1000);
		std::string newTitle = viewer.windowName + "   -   " + FPS + "FPS / " + ms + "ms";
		glfwSetWindowTitle(viewer.window, newTitle.c_str());

		// Resets times and counter
		viewer.prevTime = viewer.crntTime;
		viewer.counter = 0;

		// Use this if you have disabled VSync
		//camera.Inputs(window);
	}
}
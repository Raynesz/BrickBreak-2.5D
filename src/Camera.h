#pragma once

class Camera
{
public:
	// Stores the main vectors of the camera
	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 cameraMatrix = glm::mat4(1.0f);

	int type = 0;
	bool locked = false;

	// Prevents the camera from jumping around when first clicking left click
	bool firstClick = true;

	// Stores the width and height of the window
	int width = 0;
	int height = 0;

	// Adjust the speed of the camera and it's sensitivity when looking around
	float speed = 5.0f;
	float sensitivity = 5000.0f;

	// Camera constructor to set up initial values
	void Set(int width, int height, int type, bool locked, glm::vec3 position, glm::vec3 orientation);
	// Updates the camera matrix to the Vertex Shader
	void updateMatrix(float FOVdeg, float nearPlane, float farPlane);
	// Exports the camera matrix to a shader
	void Matrix(Shader& shader, const char* uniform);
	// Handles camera inputs
	void Inputs(GLFWwindow* window, float);
	void useFreeFPV(GLFWwindow*, float);
	void useClickFPV(GLFWwindow*, float);
};

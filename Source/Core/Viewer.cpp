#include "Viewer.h"

Viewer::Viewer(std::string windowName, SoLoud::Soloud& _soloud) : soloud(_soloud) {
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
		glfwWindowHint(GLFW_RED_BITS, mode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

		window = glfwCreateWindow(width, height, windowName.c_str(), primary, NULL);

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

		// Load GLAD so it configures OpenGL
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

		TextInit();
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
	skybox.Draw(shaders[1].program, camera, width, height);
}

void Viewer::drawEntities(Camera& camera, std::vector<Entity*> entities) {
	for (int i = 0; i < entities.size(); i++) {
		if (!entities[i]->destroyed) models[entities[i]->modelIndex].model.Draw(shaders[entities[i]->shaderIndex].program,
			camera, entities[i]->position, entities[i]->rotation, entities[i]->scale, entities[i]->baseColor);
	}
}

void Viewer::Inputs() {
	
}

void Viewer::FpsCounter() {
	currentTime = glfwGetTime();
	dt = currentTime - previousTime;
	if (dt > 0.1) dt = 0.1;

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

void Viewer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
	// activate corresponding render state	
	shaders[0].program.Activate();
	glUniform3f(glGetUniformLocation(shaders[0].program.ID, "textColor"), color.x, color.y, color.z);
	glActiveTexture(GL_TEXTURE0);
	glBindVertexArray(textVAO);

	// iterate through all characters
	std::string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = textCharacters[*c];

		float xpos = x + ch.Bearing.x * scale;
		float ypos = y - (ch.Size.y - ch.Bearing.y) * scale;

		float w = ch.Size.x * scale;
		float h = ch.Size.y * scale;
		// update VBO for each character
		float vertices[6][4] = {
			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos,     ypos,       0.0f, 1.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },

			{ xpos,     ypos + h,   0.0f, 0.0f },
			{ xpos + w, ypos,       1.0f, 1.0f },
			{ xpos + w, ypos + h,   1.0f, 0.0f }
		};
		// render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, textVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

int Viewer::TextInit() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	Shader shader("Resources/Shaders/text.vert", "Resources/Shaders/text.frag");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height));
	shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	shaders.push_back(shaderStruct("text", shader));

	// FreeType
	// --------
	FT_Library ft;
	// All functions return a value different than 0 whenever an error occurred
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
		return -1;
	}

	// find path to font
	std::string font_name = "Core/Fonts/RussoOne-Regular.ttf";
	if (font_name.empty())
	{
		std::cout << "ERROR::FREETYPE: Failed to load font_name" << std::endl;
		return -1;
	}

	// load font as face
	FT_Face face;
	if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
		std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
		return -1;
	}
	else {
		// set size to load glyphs as
		FT_Set_Pixel_Sizes(face, 0, 48);

		// disable byte-alignment restriction
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

		// load first 128 characters of ASCII set
		for (unsigned char c = 0; c < 128; c++)
		{
			// Load character glyph 
			if (FT_Load_Char(face, c, FT_LOAD_RENDER))
			{
				std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
				continue;
			}
			// generate texture
			unsigned int texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				face->glyph->bitmap.width,
				face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				face->glyph->bitmap.buffer
			);
			// set texture options
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// now store character for later use
			Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				static_cast<unsigned int>(face->glyph->advance.x)
			};
			textCharacters.insert(std::pair<char, Character>(c, character));
		}
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	// destroy FreeType once we're finished
	FT_Done_Face(face);
	FT_Done_FreeType(ft);


	// configure VAO/VBO for texture quads
	// -----------------------------------
	glGenVertexArrays(1, &textVAO);
	glGenBuffers(1, &textVBO);
	glBindVertexArray(textVAO);
	glBindBuffer(GL_ARRAY_BUFFER, textVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

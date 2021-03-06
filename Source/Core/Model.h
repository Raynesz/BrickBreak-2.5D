#pragma once

class Model
{
public:
	std::vector<Mesh> meshes;
	std::vector<Texture> loadedTex;

	// Loads in a model from a file and stores tha information in 'data', 'JSON', and 'file'
	Model(const char* file, unsigned int instancing = 1, std::vector<glm::mat4> instanceMatrix = {});

	void Draw
	(
		Shader& shader,
		Camera& camera,
		glm::vec3 translation,
		glm::quat rotation,
		glm::vec3 scale,
		glm::vec4 baseColor
	);

private:
	// Variables for easy access
	const char* file;
	std::vector<unsigned char> data;
	nlohmann::json JSON;
	// Holds number of instances (if 1 the mesh will be rendered normally)
	unsigned int instancing;

	// All the meshes and transformations
	std::vector<glm::vec3> translationsMeshes;
	std::vector<glm::quat> rotationsMeshes;
	std::vector<glm::vec3> scalesMeshes;
	std::vector<glm::mat4> matricesMeshes;
	std::vector<glm::mat4> instanceMatrix;

	// Prevents textures from being loaded twice
	std::vector<std::string> loadedTexName;

	// Loads a single mesh by its index
	void loadMesh(unsigned int indMesh);

	// Traverses a node recursively, so it essentially traverses all connected nodes
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	// Gets the binary data from a file
	std::vector<unsigned char> getData();
	// Interprets the binary data into floats, indices, and textures
	std::vector<float> getFloats(nlohmann::json accessor);
	std::vector<GLuint> getIndices(nlohmann::json accessor);
	std::vector<Texture> getTextures();

	// Assembles all the floats into vertices
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	// Helps with the assembly from above by grouping floats
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

struct modelStruct {
	std::string name;
	Model model;
};

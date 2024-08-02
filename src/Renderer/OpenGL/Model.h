#ifndef MODEL_CLASS_H
#define MODEL_CLASS_H

#include <json/json.h>

#include "Shader.h"
#include "Mesh.h"

using json = nlohmann::json;

/**
 * @class Model
 * 
 * @brief Represents a 3D model in .gltf format as colection of Meshes
 */
class Model
{
public:
	/**
	* @brief Model class constructor
	*
	* @param filepath path to model file in .gltf format
	*/
	Model(const char* filePath);

	/**
	 * @brief Draws Model using the specified shader and camera, with given position, rotation and scale
	 *
	 * @param shader The shader used for rendering.
	 * @param camera The camera used for rendering
	 * @param translation translation of Model (default = glm::vec3(0.0f, 0.0f, 0.0f), //no effect)
	 * @param rotation rotation of Model in form of quatermion (default = glm::quat(1.0f, 0.0f, 0.0f, 0.0f), //no effect)
	 * @param scale scale of Model (default = glm::vec3(0.0f, 0.0f, 0.0f), //no effect)
	 */
	void Draw(
		Shader& shader,
		Camera& camera,
		glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
		glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
		glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
	);

private:
	const char* file; ///< path to .gltf file
	std::vector<unsigned char> data; ///< vector containing 

	// TO DO: DELETE THIS AND OBJ LOADER CLASS - NOT WORKING
	void loadOBJ(const char* path);


	//GLTF Stuff
	json JSON; ///< json object containing data of the model

	std::vector<Mesh> meshes; ///< vector containing model's meshes
	std::vector<glm::vec3> translationsMeshes; ///< vector containing translation of each of model's meshes
	std::vector<glm::quat> rotationsMeshes; ///< vector containing rotarion of each of model's meshes
	std::vector<glm::vec3> scalesMeshes; ///< vector containing scale of each of model's meshes
	std::vector<glm::mat4> matricesMeshes; ///< vector containing metrix of each of model's meshes

	std::vector<std::string> loadedTexName; ///< vectors keeps names of loaded texures
	std::vector<Texture> loadedTex; ///< vector containing loaded textures

	/**
	* @brief loads mesh under given index from file
	*
	* @param indMesh index of mesh to be loaded
	*/
	void loadMesh(unsigned int indMesh);

	/**
	* @brief method used to traverse nodes of .gltf file
	* 
	* @param nextNode index of the next json node
	* @matrix translation matrix of previous node (default = glm::mat4(1.0f) //no effect)
	*/
	void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

	/**
	* @brief loads raw data from file
	*
	* @return vector of bytes
	*/
	std::vector<unsigned char> getData();

	/**
	* @brief gets float values within given accessor
	*
	* @param accessor json accessor
	* @return vector of floats representing vertex data
	*/
	std::vector<float> getFloats(json accessor);

	/**
	* @brief gets indices values within given accessor
	*
	* @param accessor json accessor
	* @return vector of GLuints representing indeces of mesh
	*/
	std::vector<GLuint> getIndices(json accessor);

	/**
	* @brief gets textures of Model
	*
	* @return vector of Textures representing tetxures of model
	*/
	std::vector<Texture> getTextures();

	/**
	* @brief creates vector of vertices from vectors with positions, normals and texture coordinates
	*
	* @return vector of vetrices
	*/
	std::vector<Vertex> assembleVertices
	(
		std::vector<glm::vec3> positions,
		std::vector<glm::vec3> normals,
		std::vector<glm::vec2> texUVs
	);

	/**
	* @brief groups float values form collection into a vector of glm::vec2
	*
	* @param floatVec vector of float values
	* @return vector of vec2's
	*/
	std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);

	/**
	* @brief groups float values form collection into a vector of glm::vec3
	*
	* @param floatVec vector of float values
	* @return vector of vec3's
	*/
	std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);

	/**
	* @brief groups float values form collection into a vector of glm::vec4
	*
	* @param floatVec vector of float values
	* @return vector of vec4's
	*/
	std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};
#endif // !MODEL_CLASS_H

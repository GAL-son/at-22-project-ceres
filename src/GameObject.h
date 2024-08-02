#ifndef GAMEOBJECT_CLASS_H
#define GAMEOBJECT_CLASS_H

#include "Renderer/Object.h"
#include "Renderer/OpenGL/Model.h"

/**
 * @class GameObject
 *
 * @brief A base class for game objects.
 */
class GameObject : public Object
{
public:
	/**
	 * @brief Destructor for the GameObject class.
	 */
	virtual ~GameObject();

	/**
	 * @brief Adds a model to the game object.
	 *
	 * @param path The path to the model file.
	 */
	void addModel(const char* path);

	/**
	 * @brief Draws the game object.
	 *
	 * @param shader The shader to use for rendering.
	 * @param camera The camera to use for rendering.
	 */
	virtual void draw(Shader& shader, Camera& camera) override;

	/**
	 * @brief Gets the active model of the game object.
	 *
	 * @return The active model.
	 */
	Model& getModel();

	/**
	 * @brief Updates the game object.
	 *
	 * @param timestep The timestep for the update.
	 */
	virtual void onUpdate(Timestep timestep) = 0;
	
private:
	Model* activeModel; /**< The active model of the game object. */
	std::vector<Model> models; /**< The models associated with the game object. */
	
};
#endif // !GAMEOBJECT_CLASS_H

#ifndef LAYER_CLASS_H
#define LAYER_CLASS_H

#include "Events/Event.h"
#include "Core/Timestep.h"

/**
 * @class Layer
 *
 * @brief A base class for layers in the application.
 */
class Layer
{
public:
	/**
	 * @brief Constructor for the Layer class.
	 *
	 * @param name The name of the layer.
	 */
	Layer(const std::string& name = "layer");

	/**
	 * @brief Destructor for the Layer class.
	 */
	virtual ~Layer();

	/**
	 * @brief Called when the layer is attached.
	 */
	virtual void onAttach() {};

	/**
	 * @brief Called when the layer is detached.
	 */
	virtual void onDetach() {};

	/**
	 * @brief Called when the layer is updated.
	 *
	 * @param ts The timestep for the update.
	 */
	virtual void onUpdate(Timestep ts) {};

	/**
	 * @brief Called when an event occurs.
	 *
	 * @param event The event that occurred.
	 */
	virtual void onEvent(Event& event) {};

	/**
	 * @brief Gets the name of the layer.
	 *
	 * @return The name of the layer.
	 */
	inline const std::string& getName() const { return layerDebugName; }

private:
	std::string layerDebugName; /**< The name of the layer. */
};


#endif // !LAYER_CLASS_H

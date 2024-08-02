#ifndef LAYER_STACK_CLASS_H
#define LAYER_STACK_CLASS_H

#include <vector>
#include "Layer.h"

/**
 * @class LayerStack
 *
 * @brief A stack of layers in the application.
 */
class LayerStack
{
public:
	/**
	 * @brief Constructor for the LayerStack class.
	 */
	LayerStack();

	/**
	 * @brief Destructor for the LayerStack class.
	 */
	~LayerStack();

	/**
	 * @brief Pushes a layer to the layer stack.
	 *
	 * @param layer The layer to push.
	 */
	void pushLayer(Layer* layer);

	/**
	 * @brief Pushes an overlay layer to the layer stack.
	 *
	 * @param overlay The overlay layer to push.
	 */
	void pushOverlay(Layer* overlay);

	/**
	 * @brief Pops a layer from the layer stack.
	 *
	 * @param layer The layer to pop.
	 */
	void popLayer(Layer* layer);

	/**
	 * @brief Pops an overlay layer from the layer stack.
	 *
	 * @param overlay The overlay layer to pop.
	 */
	void popOverlay(Layer* overlay);

	/**
	 * @brief Returns an iterator pointing to the beginning of the layer stack.
	 *
	 * @return An iterator pointing to the beginning of the layer stack.
	 */
	std::vector<Layer*>::iterator begin() { return layers.begin(); }

	/**
	 * @brief Returns an iterator pointing to the end of the layer stack.
	 *
	 * @return An iterator pointing to the end of the layer stack.
	 */
	std::vector<Layer*>::iterator end() { return layers.end(); }

private:
	std::vector<Layer*> layers; /**< The vector of layers in the stack. */
	std::vector<Layer*>::iterator layerInsert; /**< Iterator for inserting new layers in the stack. */
};

#endif // !LAYER_STACK_CLASS_H

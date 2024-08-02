#include "Map.h"

Map::Map(const char* path)
{
	addModel(path);
	setPosition(0.0, 1.0, 0.0);
	setScale(1.0, 1.2, 1.0);
}
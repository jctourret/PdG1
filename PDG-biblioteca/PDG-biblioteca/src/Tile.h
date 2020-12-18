#pragma once
#include "Exports.h"
#include "Sprite.h"

class SABASAENGINE_API Tile: public Sprite
{
	int _id;
public:
	bool _isWalkable;
	Tile(Renderer* renderer, unsigned int newTexture, bool transparency, int id, float width, float heigth);
	void setWalkable(bool isWalkable);
	Tile* clone();
	~Tile();
};

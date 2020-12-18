#include "Tile.h"

Tile::Tile(Renderer* renderer, unsigned int newTexture, bool transparency, int id, float scaleX, float scaleY):Sprite(renderer, newTexture, transparency,scaleX,scaleY)
{
	_id = id;
	_isWalkable = true;
}

void Tile::setWalkable(bool isWalkable)
{
	_isWalkable = isWalkable;
}

Tile* Tile::clone()
{
	Tile* clonedTile = new Tile(rend, texture, _transparency, _id, _scaleX, _scaleY);
	clonedTile->setTextureCoordinates(verticesData[3], verticesData[4], verticesData[8], verticesData[9], verticesData[13], verticesData[14], verticesData[18], verticesData[19]);	
	return clonedTile;
}

Tile::~Tile()
{

}
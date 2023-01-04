#pragma once
#include <vector>
#include <REngine.h>
class Tilemap
{
public:
	void LoadTilemap(const char* tilemap, int tileSize);

	void LoadTiles(const char* tilesPath);

	void Render();
private:
	std::vector<int> mTilemap;
	std::vector<Texture2D> mTilemapTextures;
	int mRows;
	int mCollumns;
	int mTileSize;
};


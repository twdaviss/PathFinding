#pragma once
#include <REngine.h>
#include <AI.h>
class Tilemap
{
public:
	void LoadTilemap(const char* tilemap, int tileSize);

	void LoadTiles(const char* tilesPath);

	void Render();
	void Unload();
	struct Tile {
		Texture2D texture;
		int weight;
	};
private:
	std::vector<int> mTilemap;
	std::vector<Tile*> mTiles;
	AI::GridBasedGraph mGridBasedGraph;
	int mRows;
	int mCollumns;
	int mTileSize;
};


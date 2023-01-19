#include "Tilemap.h"
#include <fstream>
void Tilemap::LoadTilemap(const char* tilemap, int tileSize)
{
	mTileSize = tileSize;
	std::string contents;
	std::ifstream path(tilemap);
	int tiles = 0;
	int rows = 0;
	if (!path.is_open()) {
		return;
	}
	while (path >> contents) {
		for (int i = 0; i < contents.size();i++) {
			mTilemap.push_back(contents[i]-48);
			tiles++;
		}
		rows++;
	}
	mRows = rows;
	mCollumns = tiles/rows;
	mGridBasedGraph.Initialize(mCollumns,mRows);
}

void Tilemap::LoadTiles(const char* tilesPath)
{
	std::string contents;
	std::string fullPath;
	std::ifstream path(tilesPath);
	Texture2D texture;
	int weight = 0;
	if (!path.is_open()) {
		return;
	}

	std::string tileCount;
	std::getline(path, tileCount);
	Tile *tile;
	while (path >> contents) {
		REng::ResourcesFullPath(contents, fullPath);
		texture = LoadTexture(fullPath.c_str());
		std::getline(path,contents);
		weight = stoi(contents);
		tile = (struct Tile*)malloc(sizeof(struct Tile));
		tile->texture = texture;
		tile->weight = weight;
		mTiles.push_back(tile);
	}
}

void Tilemap::Render()
{
	Texture2D texture;
	int currentTile = 0;
	for (int rows = 0; rows < mRows; rows++) {
		for (int collumns = 0; collumns < mCollumns; collumns++) {
			texture = mTiles[mTilemap[currentTile]]->texture;
			DrawTexture(texture,collumns*mTileSize,rows*mTileSize,WHITE);
			currentTile++;
		}
	}




}

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
	while (getline(path, contents)) {
		for (int i = 0; i < contents.size();i++) {
			mTilemap.push_back(contents[i]-48);
			tiles++;
		}
		rows++;
	}
	mRows = rows;
	mCollumns = tiles/rows;
}

void Tilemap::LoadTiles(const char* tilesPath)
{
	std::string contents;
	std::string fullPath;
	std::ifstream path(tilesPath);
	Texture2D texture;
	if (!path.is_open()) {
		return;
	}
	while (path >> contents) {
		REng::ResourcesFullPath(contents, fullPath);
		texture = LoadTexture(fullPath.c_str());
		mTilemapTextures.push_back(texture);
	}
}

void Tilemap::Render()
{
	Texture2D texture;
	int currentTile = 0;
	for (int rows = 0; rows < mRows; rows++) {
		for (int collumns = 0; collumns < mCollumns; collumns++) {
			texture = mTilemapTextures[mTilemap[currentTile]];
			DrawTexture(texture,collumns*mTileSize,rows*mTileSize,WHITE);
			currentTile++;
		}
	}




}

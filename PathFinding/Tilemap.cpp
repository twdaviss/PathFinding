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

void Tilemap::Render(bool debug)
{
	using AI::GridBasedGraph;
	Texture2D texture;
	int currentTile = 0;
	GridBasedGraph::Node* currentNode;
	for (int rows = 0; rows < mRows; rows++) {
		for (int collumns = 0; collumns < mCollumns; collumns++) {
			texture = mTiles[mTilemap[currentTile]]->texture;
			DrawTexture(texture,collumns*mTileSize,rows*mTileSize,WHITE);

			if (debug) {
				if (Tilemap::GetTile(collumns,rows)->weight >= 6) {
					break;
				}
				currentNode = mGridBasedGraph.GetNode(collumns, rows);
					
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::North]->collumn, currentNode->neighbours[GridBasedGraph::Directions::North]->row,BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::NorthEast]->collumn, currentNode->neighbours[GridBasedGraph::Directions::NorthEast]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::East]->collumn, currentNode->neighbours[GridBasedGraph::Directions::East]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::SouthEast]->collumn, currentNode->neighbours[GridBasedGraph::Directions::SouthEast]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::South]->collumn, currentNode->neighbours[GridBasedGraph::Directions::South]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::SouthWest]->collumn, currentNode->neighbours[GridBasedGraph::Directions::SouthWest]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::West]->collumn, currentNode->neighbours[GridBasedGraph::Directions::West]->row, BLACK);
				DrawLine(collumns, rows, currentNode->neighbours[GridBasedGraph::Directions::NorthWest]->collumn, currentNode->neighbours[GridBasedGraph::Directions::NorthWest]->row, BLACK);
			}

			currentTile++;
		}
	}
}
void Tilemap::Unload() {
	mGridBasedGraph.~GridBasedGraph();
}
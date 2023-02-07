#include "Tilemap.h"
#include <fstream>
using namespace AI;
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

	auto GetNeighbour = [&](int x, int y)->GridBasedGraph::Node* {
		auto node = mGridBasedGraph.GetNode(x, y);

		if (node == nullptr) {
			return nullptr;
		}
		if (isBlocked(x, y)) {
			return nullptr;
		}
		return node;
	};


	for (int y = 0; y < mRows; y++) {
		for (int x = 0; x < mCollumns; x++) {
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::North] = GetNeighbour(x,y-1);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::NorthEast] = GetNeighbour(x+1,y-1);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::East] = GetNeighbour(x+1,y);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::SouthEast] = GetNeighbour(x+1,y+1);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::South] = GetNeighbour(x,y+1);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::SouthWest] = GetNeighbour(x-1,y+1);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::West] = GetNeighbour(x-1,y);
			mGridBasedGraph.GetNode(x, y)->neighbours[GridBasedGraph::NorthWest] = GetNeighbour(x-1,y-1);
		}
	}

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
	int startX = 0.5 * mTileSize;
	int startY = 0.5 * mTileSize;
	for (int x = 0; x < mRows; x++) {
		for (int y = 0; y < mCollumns; y++) {
			texture = mTiles[mTilemap[currentTile]]->texture;
			DrawTexture(texture,y*mTileSize,x*mTileSize,WHITE);

			if (debug) {
				if (mTiles[mTilemap[currentTile]]->weight >= 6) {
					currentTile++;
					startX += mTileSize;
					continue;
				}
				currentNode = mGridBasedGraph.GetNode(y, x);
				
				if (currentNode->neighbours[GridBasedGraph::Directions::North]) {
					DrawLine(startX, startY,startX,startY-mTileSize , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::NorthEast]) { 
					DrawLine(startX, startY,startX + mTileSize ,startY - mTileSize , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::East]) { 
					DrawLine(startX, startY, startX + mTileSize,startY , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::SouthEast]) { 
					DrawLine(startX, startY,startX + mTileSize ,startY + mTileSize , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::South]) { 
					DrawLine(startX, startY,startX, startY + mTileSize , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::SouthWest]) { 
					DrawLine(startX, startY,startX - mTileSize, startY + mTileSize , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::West]) { 
					DrawLine(startX, startY,startX - mTileSize, startY , BLACK); }
				if (currentNode->neighbours[GridBasedGraph::Directions::NorthWest]) { 
					DrawLine(startX, startY,startX - mTileSize, startY-mTileSize , BLACK); }
				startX += mTileSize;
			}

			currentTile++;
		}
		startX = 0.5 * mTileSize;
		startY += mTileSize;
	}
}
void Tilemap::Unload() {
	mGridBasedGraph.~GridBasedGraph();
}
bool Tilemap::isBlocked(int x, int y)const {
	return mTiles[mTilemap[y * mCollumns + x]]->weight >= 6;
}
int Tilemap::ToIndex(int x, int y) {
	return y * mCollumns + x;
}

std::vector<REng::Math::Vector2> Tilemap::FindPath(int startX, int startY, int endX, int endY)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;
	BFS bfs;
	REng::Math::Vector2 pos;

	if (bfs.Run(mGridBasedGraph, startX, startY, endX, endY)) {
		closedList = bfs.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr) {
			path.push_back(GetPixelPosition(node->collumn,node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
std::vector<REng::Math::Vector2> Tilemap::FindPathDijkstra(int startX, int startY, int endX, int endY)
{
	std::vector<REng::Math::Vector2> path;
	NodeList closedList;
	Dijkstra ds;
	REng::Math::Vector2 pos;
	auto GetCostWrapper = [&](GridBasedGraph::Node* node) {
		return GetCost(node);
	};

	if (ds.Run(mGridBasedGraph, startX, startY, endX, endY, GetCostWrapper)) {
		closedList = ds.GetClosedList();
		auto node = closedList.back();
		while (node != nullptr) {
			path.push_back(GetPixelPosition(node->collumn, node->row));
			node = node->parent;
		}
		std::reverse(path.begin(), path.end());
	}
	return path;
}
REng::Math::Vector2 Tilemap::GetPixelPosition(int x, int y) {
	return { (float)x,(float)y };
}

float Tilemap::GetCost(AI::GridBasedGraph::Node* node){

	if (mTiles[mTilemap[ToIndex(node->collumn, node->row)]]->weight > 0) {
		return 5;
	}
	else {
		return 1;
	}

}
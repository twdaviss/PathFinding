#pragma once
#include <REngine.h>
#include <AI.h>
class Tilemap
{
public:
	void LoadTilemap(const char* tilemap, int tileSize);

	void LoadTiles(const char* tilesPath);

	void Render(bool debug);
	void Unload();
	bool isBlocked(int x, int y) const;
	int ToIndex(int x, int y);
	struct Tile {
		Texture2D texture;
		int weight;
	};
	Tile* GetTile(int num) {
		return mTiles[num];
	}
	std::vector<REng::Math::Vector2> FindPath(int startX, int startY, int endX, int endY);
	std::vector<REng::Math::Vector2> FindPathDijkstra(int startX, int startY, int endX, int endY);
	std::vector<REng::Math::Vector2> FindPathAStar(int startX, int startY, int endX, int endY);
	REng::Math::Vector2 GetPixelPosition(int x, int y) const;
	float GetCost(AI::GridBasedGraph::Node*);
	float GetGuess(AI::GridBasedGraph::Node* node, AI::GridBasedGraph::Node* endNode);
private:
	std::vector<int> mTilemap;
	std::vector<Tile*> mTiles;
	AI::GridBasedGraph mGridBasedGraph;
	int mRows;
	int mCollumns;
	int mTileSize;

};



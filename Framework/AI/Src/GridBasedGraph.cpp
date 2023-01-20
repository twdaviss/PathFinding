#include "pch.h"
#include "GridBasedGraph.h"

void AI::GridBasedGraph::Initialize(int collumns, int rows)
{
	mCollumns = collumns;
	mRows = rows;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			Node* node;
			node = (struct Node*)malloc(sizeof(struct Node));
			node->collumn = j;
			node->row = i;
			mNodes.push_back(node);
			/*Tile* tile;
			tile = (struct Tile*)malloc(sizeof(struct Tile));
			tile->texture = texture;
			tile->weight = weight;
			mTiles.push_back(tile);*/
		}
	}
	SetNeighbours();
}

AI::GridBasedGraph::Node* AI::GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || y < 0) {
		return 0;
	}
	auto it = std::find_if(mNodes.begin(), mNodes.end(), [x,y](const Node* obj) {if (obj->collumn == x && obj->row == y) { return obj; }});
	return *it;
}

const AI::GridBasedGraph::Node* AI::GridBasedGraph::GetNode(int x, int y) const
{
	return nullptr;
}

int AI::GridBasedGraph::GetCollumns() const
{
	return mCollumns;
}

int AI::GridBasedGraph::GetRows() const
{
	return mRows;
}

void AI::GridBasedGraph::SetNeighbours() {
	for (int row = 0; row < mRows; row++) {
		for (int collumn = 0; collumn < mCollumns; collumn++) {
			GetNode(row, collumn)->neighbours[North] = GetNode(row-1, collumn);
			GetNode(row, collumn)->neighbours[NorthEast] = GetNode(row-1, collumn+1);
			GetNode(row, collumn)->neighbours[East] = GetNode(row, collumn+1);
			GetNode(row, collumn)->neighbours[SouthEast] = GetNode(row+1, collumn+1);
			GetNode(row, collumn)->neighbours[South] = GetNode(row+1, collumn);
			GetNode(row, collumn)->neighbours[SouthWest] = GetNode(row+1, collumn-1);
			GetNode(row, collumn)->neighbours[West] = GetNode(row, collumn-1);
			GetNode(row, collumn)->neighbours[NorthWest] = GetNode(row-1, collumn-1);
		}
	}
}

AI::GridBasedGraph::~GridBasedGraph()
{
	for(auto &elem:mNodes)
	{
		free(elem);
	}
}

int AI::GridBasedGraph::GetIndex(int x, int y) const
{
	auto it = std::find_if(mNodes.begin(), mNodes.end(), [x, y](const Node* obj) {if (obj->collumn == x && obj->row == y){ return obj; }});
	if (it != mNodes.end())
	{
		int index = std::distance(mNodes.begin(), it);
		return index;
	}
}

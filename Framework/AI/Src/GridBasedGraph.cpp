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
		return NULL;
	}
	//auto it = find_if(v.begin(), v.end(), [&myString](const Type& obj) {return obj.getName() == myString; })

	for (Node* element: mNodes)
	{
		if (element->collumn == x && element->row == y) {
			return element;
		}
	}
	return NULL;
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
			GetNode(collumn, row)->neighbours[North] = GetNode(collumn, row-1);
			GetNode(collumn, row)->neighbours[NorthEast] = GetNode(collumn+1,row - 1 );
			GetNode(collumn, row)->neighbours[East] = GetNode(collumn + 1,row);
			GetNode(collumn, row)->neighbours[SouthEast] = GetNode(collumn + 1,row+1);
			GetNode(collumn, row)->neighbours[South] = GetNode(collumn,row+1);
			GetNode(collumn, row)->neighbours[SouthWest] = GetNode(collumn-1, row + 1);
			GetNode(collumn, row)->neighbours[West] = GetNode(collumn-1, row);
			GetNode(collumn, row)->neighbours[NorthWest] = GetNode(collumn-1, row - 1);
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

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
	//SetNeighbours();
}

AI::GridBasedGraph::Node* AI::GridBasedGraph::GetNode(int x, int y)
{
	if (x < 0 || y < 0) {
		return nullptr;
	}
	//auto it = find_if(v.begin(), v.end(), [&myString](const Type& obj) {return obj.getName() == myString; })

	for (Node* element: mNodes)
	{
		if (element->collumn == x && element->row == y) {
			return element;
		}
	}
	return nullptr;
}

const AI::GridBasedGraph::Node* AI::GridBasedGraph::GetNode(int x, int y) const
{
	if (x < 0 || y < 0) {
		return nullptr;
	}
	//auto it = find_if(v.begin(), v.end(), [&myString](const Type& obj) {return obj.getName() == myString; })

	for (Node* element : mNodes)
	{
		if (element->collumn == x && element->row == y) {
			return element;
		}
	}
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



AI::GridBasedGraph::~GridBasedGraph()
{
	for(auto &elem:mNodes)
	{
		free(elem);
	}
}

int AI::GridBasedGraph::GetIndex(int x, int y) const
{
	return y * mCollumns + x;
}
void AI::GridBasedGraph::ResetSearchParameters() const
{
	for (Node* node : mNodes) {
		node->parent = nullptr;
		node->opened = false;
		node->closed = false;
		node->cost = 0.0f;
	}
}


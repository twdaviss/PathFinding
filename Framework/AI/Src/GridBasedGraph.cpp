#include "pch.h"
#include "GridBasedGraph.h"

void AI::GridBasedGraph::Initialize(int collumns, int rows)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < collumns; j++) {
			Node node;
			node.collumn = j;
			node.row = i;
			mNodes.push_back(&node);
		}
	}
}

AI::GridBasedGraph::Node* AI::GridBasedGraph::GetNode(int x, int y)
{
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

int AI::GridBasedGraph::GetIndex(int x, int y) const
{
	auto it = std::find_if(mNodes.begin(), mNodes.end(), [x, y](const Node* obj) {if (obj->collumn == x && obj->row == y){ return obj; }});
	if (it != mNodes.end())
	{
		int index = std::distance(mNodes.begin(), it);
		return index;
	}
}

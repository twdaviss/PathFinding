#pragma once
#include "GridBasedGraph.h"
namespace AI 
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(GridBasedGraph::Node*)>;
	using GetGuess = std::function<float(GridBasedGraph::Node*, GridBasedGraph::Node*)>;

	class AStar
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetGuess getGuess);
		const NodeList& GetClosedList() const { return mClosedList; }
	private:
		NodeList mOpenList;
		NodeList mClosedList;
	};
}

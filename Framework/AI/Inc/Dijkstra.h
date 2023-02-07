#pragma once
#include "GridBasedGraph.h"
namespace AI 
{
	using NodeList = std::list<GridBasedGraph::Node*>;
	using GetCost = std::function<float(GridBasedGraph::Node*)>;
	class Dijkstra
	{
	public:
		bool Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost GetCost);
		const NodeList& GetClosedList() const { return mClosedList; }
	private:
		NodeList mOpenList;
		NodeList mClosedList;
		int TravelCost(GridBasedGraph::Node node1, GridBasedGraph::Node node2);

	};
}

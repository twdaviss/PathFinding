#include "pch.h"
#include "Dijkstra.h"
using namespace AI;
bool AI::Dijkstra::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost GetCost)
{
    
    graph.ResetSearchParameters();
    mOpenList.clear();
    mClosedList.clear();

    auto startNode = graph.GetNode(startX, startY);
    auto endNode = graph.GetNode(endX, endY);
    mOpenList.push_back(startNode);
    startNode->opened = true;

    bool endFound = false;
    GridBasedGraph::Node* currentNode;

    while (!endFound && !mOpenList.empty()) {
        currentNode = mOpenList.front();
        mOpenList.pop_front();

        if (currentNode == endNode) {
            endFound = true;
        }
        else {
            for (auto& node : currentNode->neighbours) {
                if (node == nullptr || node->closed){
                    continue;
                }
                if (!node->opened) {
                    node->opened == true;
                    node->parent = currentNode;

                    node->cost = currentNode->cost + GetCost(node);
                 
                    mOpenList.push_back(node);
                    mOpenList.sort();
                }
                else if (node->cost > currentNode->cost + GetCost(node)) { //edge relaxation
                    node->cost = currentNode->cost + GetCost(node);
                    node->parent = currentNode;
                }
            }
        }
        currentNode->closed = true;
        mClosedList.push_back(currentNode);
    }
    if (endFound == true) {
        return true;
    }
    else {
        return false;
    }

}
int AI::Dijkstra::TravelCost(GridBasedGraph::Node node1, GridBasedGraph::Node node2) {
    return sqrt(abs(node1.collumn - node2.collumn) ^ 2 + abs(node1.row - node2.row) ^ 2);
}

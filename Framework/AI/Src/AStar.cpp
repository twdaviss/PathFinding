#include "pch.h"
#include "AStar.h"
using namespace AI;
bool AI::AStar::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY, GetCost getCost, GetGuess getGuess)
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
                    node->opened = true;
                    node->parent = currentNode;

                    node->cost = currentNode->cost + getCost(node);
                    node->guess = getGuess(node,endNode);

                 
                    mOpenList.push_back(node);
                    mOpenList.sort();
                }
                else if (node->cost > currentNode->cost + getCost(node)) { //edge relaxation
                    node->cost = currentNode->cost + getCost(node);
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

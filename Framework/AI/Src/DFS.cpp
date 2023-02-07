#include "pch.h"
#include "DFS.h"
using namespace AI;
bool AI::DFS::Run(GridBasedGraph& graph, int startX, int startY, int endX, int endY)
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
        if (currentNode == endNode) {
            endFound = true;
            mClosedList.push_back(currentNode);
            currentNode->closed = true;
            mOpenList.pop_front();
            break;
        }
        else {
            for (auto& node : currentNode->neighbours) {
                if (node != nullptr && !node->opened && !node->closed) {
                    mOpenList.push_front(node); //adding neighbours to FRONT of list for DFS
                    node->opened = true;
                    node->parent = currentNode;
                }
            }
        }
        mClosedList.push_back(currentNode);
        currentNode->closed = true;
        mOpenList.pop_front();
    }
    if (endFound == true) {
        return true;
    }
    else {
        return false;
    }

}

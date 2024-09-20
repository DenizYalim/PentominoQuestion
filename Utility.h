// Utility.h
#ifndef UTILITY_H
#define UTILITY_H

#include <vector>
#include <tuple>
#include <queue>

// Forward declaration of the Graph class
class Graph;

// Function declarations
void exploreNeighbors(int row, int column,
                      std::queue<int>& rowQueue, std::queue<int>& columnQueue,
                      std::vector<std::vector<bool>>& visited, const Graph& graph,
                      int& nodes_left_in_layer, int& nodes_in_next_layer);

std::tuple<int, int, int> bfs(const Graph& graph, int starterRow, int starterColumn);

int getGraphDiameter(Graph& graph);

#endif // UTILITY_H

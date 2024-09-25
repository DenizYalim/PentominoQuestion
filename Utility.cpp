// Utility.cpp
#include "Utility.h"
#include "Graph.h"  // Include the Graph class definition
#include <iostream> // For debugging or output (if needed)

void exploreNeighbors(int row, int column,
                      std::queue<int>& rowQueue, std::queue<int>& columnQueue,
                      std::vector<std::vector<bool>>& visited, const Graph& graph,
                      int& nodes_left_in_layer, int& nodes_in_next_layer) {
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; i++) {
        int rr = row + dr[i];
        int cc = column + dc[i];

        // Check if they are inside the matrix
        if (rr < 0 || cc < 0)
            continue;
        if (rr >= graph.getWidth() || cc >= graph.getHeight())
            continue;

        // Check if they've been visited or are not enterable
        if (visited[rr][cc])
            continue;
        if (graph.getGraphVec()[rr][cc] == Filled)
            continue;

        rowQueue.emplace(rr);
        columnQueue.emplace(cc);

        visited[rr][cc] = true;
        nodes_in_next_layer++;
    }
}

std::tuple<int, int, int> bfs(const Graph& graph, int starterRow, int starterColumn) {
    const auto& matrix = graph.getGraphVec();
    int width = graph.getWidth();
    int height = graph.getHeight();

    std::vector<std::vector<bool>> visited(width, std::vector<bool>(height, false));

    int moveCount = 0;
    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    std::queue<int> rowQueue;
    std::queue<int> columnQueue;

    int lastRow = starterRow;
    int lastColumn = starterColumn;

    rowQueue.emplace(starterRow);
    columnQueue.emplace(starterColumn);
    visited[starterRow][starterColumn] = true;

    while (!rowQueue.empty()) {
        int row = rowQueue.front();
        rowQueue.pop();
        int column = columnQueue.front();
        columnQueue.pop();

        exploreNeighbors(row, column, rowQueue, columnQueue, visited, graph, nodesLeftInLayer, nodesInNextLayer);
        nodesLeftInLayer--;

        // Update last node
        lastRow = row;
        lastColumn = column;

        if (nodesLeftInLayer == 0) {
            nodesLeftInLayer = nodesInNextLayer;
            nodesInNextLayer = 0;
            moveCount++;
        }
    }

    // Adjust moveCount since it increments one extra time after the last layer
    return std::make_tuple(lastRow, lastColumn, moveCount - 1);
}

int getGraphDiameter(Graph& graph) {
    int starterRow = -1;
    int starterColumn = -1;

    // Find the first empty tile to start BFS
    for (int row = 0; row < graph.getWidth(); row++) {
        bool tileEmpty = false;
        for (int column = 0; column < graph.getHeight(); column++) {
            if (graph.getGraphVec()[row][column] == Empty) {
                starterRow = row;
                starterColumn = column;
                tileEmpty = true;
                break;
            }
        }
        if (tileEmpty)
            break;
    }

    if (starterRow == -1 || starterColumn == -1) {
        // No empty tiles found
        return 0;
    }

    int firstRow, firstColumn, moveCount;
    std::tie(firstRow, firstColumn, moveCount) = bfs(graph, starterRow, starterColumn);

    graph.setStart(firstRow, firstColumn);

    int secondRow, secondColumn, diameter;
    std::tie(secondRow, secondColumn, diameter) = bfs(graph, firstRow, firstColumn);

    graph.setFinish(secondRow, secondColumn);

    // Optional: Run BFS again from the second point
    // std::tie(firstRow, firstColumn, diameter) = bfs(graph, secondRow, secondColumn);
    // graph.setStart(firstRow, firstColumn);

    return diameter;
}
#ifdef RUN_UTILITY_MAIN
int main(){
    std::cout << "Running Utility.cpp" << std::endl;

    int size = 5;

    Graph graph(size, size);
    graph.setStart(0,0);
    graph.setFinish(size -1, size -1);

    graph.fillTile(3,0);

    bool theOdd = false;
    for(int i = 1; i < size; i++){
        for (int j = 0; j < size-1; ++j) {
            if(theOdd){
                graph.fillTile(j+1, i*2 - 1);
            }
            else{
                graph.fillTile(j, i*2 - 1);
            }

        }
        theOdd = !theOdd;
    }



    graph.displayGraph();

    std::cout << getGraphDiameter(graph);

    return 1;
}
#endif
#include "Graph.h"
#include <iostream>

// Constructor
Graph::Graph(int width, int height) : width(width), height(height) {
    graphVec.resize(width, std::vector<spaceTile>(height, Empty));
}

// Check if a tile is within the graph boundaries
bool Graph::tileInGraph(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

// Get the width of the graph
int Graph::getWidth() const {
    return width;
}

// Get the height of the graph
int Graph::getHeight() const {
    return height;
}

// Fill a tile in the graph
bool Graph::fillTile(int row, int column) {
    if (!tileInGraph(row, column) || graphVec[row][column] == Filled)
        return false;

    graphVec[row][column] = Filled;
    return true;
}

// Empty a tile in the graph
bool Graph::emptyTile(int row, int column) {
    if (!tileInGraph(row, column) || graphVec[row][column] != Filled)
        return false;

    graphVec[row][column] = Empty;
    return true;
}

// Set the starting point in the graph
bool Graph::setStart(int row, int column) {
    if (!tileInGraph(row, column) || graphVec[row][column] != Empty)
        return false;

    // Remove any existing Start tile
    for (int r = 0; r < width; ++r) {
        for (int c = 0; c < height; ++c) {
            if (graphVec[r][c] == Start)
                graphVec[r][c] = Empty;
        }
    }

    graphVec[row][column] = Start;
    return true;
}

// Set the finishing point in the graph
bool Graph::setFinish(int row, int column) {
    if (!tileInGraph(row, column) || graphVec[row][column] != Empty)
        return false;

    // Remove any existing Finish tile
    for (int r = 0; r < width; ++r) {
        for (int c = 0; c < height; ++c) {
            if (graphVec[r][c] == Finish)
                graphVec[r][c] = Empty;
        }
    }

    graphVec[row][column] = Finish;
    return true;
}

// Get the graph vector
std::vector<std::vector<spaceTile>> Graph::getGraphVec() const {
    return graphVec;
}

// Display the graph
void Graph::displayGraph() const {
    for (const auto& row : graphVec) {
        for (const auto& tile : row) {
            switch (tile) {
                case Empty:
                    std::cout << " [ ] ";
                    break;
                case Filled:
                    std::cout << " [#] ";
                    break;
                case Start:
                    std::cout << " [S] ";
                    break;
                case Finish:
                    std::cout << " [F] ";
                    break;
            }
        }
        std::cout << std::endl;
    }
}

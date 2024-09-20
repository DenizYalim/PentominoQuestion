#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

// Define the possible states for each tile in the graph
enum spaceTile {
    Empty,
    Filled,
    Start,
    Finish
};

class Graph {
private:
    int width;
    int height;
    std::vector<std::vector<spaceTile>> graphVec;

public:
    // Constructor
    Graph(int width, int height);

    // Member functions
    bool tileInGraph(int x, int y) const;
    int getWidth() const;
    int getHeight() const;
    bool fillTile(int row, int column);
    bool emptyTile(int row, int column);
    bool setStart(int row, int column);
    bool setFinish(int row, int column);
    std::vector<std::vector<spaceTile>> getGraphVec() const;
    void displayGraph() const;
};

#endif // GRAPH_H

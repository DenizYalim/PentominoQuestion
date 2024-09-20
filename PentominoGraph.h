// PentominoGraph.h
#ifndef PENTAMINOGRAPH_H
#define PENTAMINOGRAPH_H

#include <unordered_map>
#include <vector>
#include "Graph.h"  // Include the Graph class

// Namespace declarations
using std::unordered_map;
using std::vector;

class PentominoGraph {
private:
    enum pieceAvailability {
        Used,
        Unused,
        Immunue
    };

    int blockCount;
    unordered_map<char, pieceAvailability> pieces;

    // Static member containing piece schematics
    static const unordered_map<char, std::pair<vector<int>, vector<int>>> pieceSchematics;

public:
    Graph graph;

    // Constructor
    PentominoGraph(int width, int height, int blockCount = 5);

    // Member functions
    bool placePiece(int row, int column, char pieceName);
    bool placeAnyPiece(int row, int column, const vector<int>& piecePosX, const vector<int>& piecePosY);
};

#endif // PENTAMINOGRAPH_H

// PentaminoGraph.cpp
#include "PentaminoGraph.h"
#include <iostream>

// Namespace declarations
using std::cout;
using std::endl;
using std::unordered_map;
using std::vector;
using std::pair;

// Initialize the static member 'pieceSchematics'
const unordered_map<char, pair<vector<int>, vector<int>>> PentaminoGraph::pieceSchematics = {
        {'P', {{0, 1, 0, 1, 0}, {0, 0, 1, 1, 2}}},
        {'I', {{0, 1, 2, 3, 4}, {0, 0, 0, 0, 0}}},
        {'V', {{0, 0, 0, 1, 2}, {0, 1, 2, 0, 0}}},
        {'U', {{0, 0, 1, 2, 2}, {0, 1, 0, 0, 1}}},
        {'X', {{0, 1, 1, 1, 2}, {1, 0, 1, 2, 1}}},
        {'F', {{0, 0, 1, 1, 2}, {1, 2, 0, 1, 1}}},
        {'W', {{0, 1, 1, 2, 2}, {0, 0, 1, 1, 2}}},
        {'T', {{0, 0, 0, 1, 2}, {0, 1, 2, 1, 1}}},
        {'Y', {{0, 1, 1, 2, 3}, {0, 0, 1, 0, 0}}},
        {'L', {{0, 0, 1, 2, 3}, {0, 1, 0, 0, 0}}},
        {'N', {{0, 0, 1, 1, 1}, {0, 1, 1, 2, 3}}},
        {'Z', {{0, 0, 1, 2, 2}, {0, 1, 1, 1, 2}}},
        {'0', {{0},{0}}} // Monomino for debugging
};

// Constructor implementation
PentaminoGraph::PentaminoGraph(int width, int height, int blockCount)
        : graph(width, height), blockCount(blockCount) {

    // Initialize 'pieces' with all pieces set to 'Unused'
    pieces = {
            {'F', Unused}, {'I', Unused}, {'L', Unused}, {'N', Unused},
            {'P', Unused}, {'T', Unused}, {'U', Unused}, {'V', Unused},
            {'W', Unused}, {'X', Unused}, {'Y', Unused}, {'Z', Unused},
            {'0', Immunue} // Monomino Piece for debugging
    };
}

// Place a specific piece on the graph
bool PentaminoGraph::placePiece(int row, int column, char pieceName) {
    // Check if the piece is available
    if (pieces[pieceName] == Used) {
        cout << "Piece " << pieceName << " has already been used." << endl;
        return false;
    }

    // Find the piece schematic
    auto it = pieceSchematics.find(pieceName);
    if (it == pieceSchematics.end()) {
        cout << "Piece '" << pieceName << "' not found in schematics." << endl;
        return false;
    }

    const auto& pieceData = it->second;

    // Attempt to place the piece
    if (placeAnyPiece(row, column, pieceData.first, pieceData.second)) {
        cout << "Piece '" << pieceName << "' placed successfully!" << endl;
        // Mark the piece as used
        if(pieces[pieceName] != Immunue)
            pieces[pieceName] = Used;
        return true;
    } else {
        cout << "Failed to place piece '" << pieceName << "'." << endl;
        return false;
    }
}

// Place any piece given its position vectors
bool PentaminoGraph::placeAnyPiece(int row, int column,
                                   const vector<int>& piecePosX,
                                   const vector<int>& piecePosY) {

    if(piecePosX.size() == 1){
        int x = row + piecePosX[0];
        int y = column + piecePosY[0];
        graph.fillTile(x,y);
        return true;
    }

    // Check if piecePosX and piecePosY have the correct size // Todo: is this really necessary? chatgpt added this, this reduces robustness and flexibility for future additions
    if (piecePosX.size() != blockCount || piecePosY.size() != blockCount) {
        cout << "Invalid piece dimensions." << endl;
        return false;
    }


    // First, verify that the piece can be placed
    for (int i = 0; i < blockCount; i++) {
        int x = row + piecePosX[i];
        int y = column + piecePosY[i];

        // Check boundaries
        if (x < 0 || x >= graph.getWidth() || y < 0 || y >= graph.getHeight()) {
            // Position is outside the graph
            return false;
        }

        // Check if tile is empty
        if (graph.getGraphVec()[x][y] != Empty) {
            // Tile is already filled or occupied
            return false;
        }
    }

    // All checks passed; place the piece
    for (int i = 0; i < blockCount; ++i) {
        int x = row + piecePosX[i];
        int y = column + piecePosY[i];
        //graph.getGraphVec()[x][y] = Filled;
        graph.fillTile(x,y);
        //cout << "filled: " << x << "," << y << endl;
    }

    return true;
}

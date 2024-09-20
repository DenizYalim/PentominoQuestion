#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <unordered_map>

#include "Graph.h"
#include "Utility.h"
#include "PentaminoGraph.h"

using namespace std;

/*class Graph {
private:
    int width;
    int height;

    vector<vector<spaceTile>> graphVec;

public:
    Graph(int width, int height) {
        this->width = width;
        this->height = height;

        graphVec.resize(width, vector<spaceTile>(height, Empty));
    }

    bool tileInGraph(int x, int y) const {
        return x < width && y < height;
    }

    int getWidth(){
        return width;
    }

    int getHeight(){
        return height;
    }

    bool fillTile(int row, int column) {
        if (!(tileInGraph(row, column) && graphVec[row][column] != Filled))
            return false;

        graphVec[row][column] = Filled;
        return true;
    }

    bool emptyTile(int row, int column) {
        if (!(tileInGraph(row, column) && graphVec[row][column] == Filled))
            return false;

        graphVec[row][column] = Empty;
        return true;
    }

    bool setStart(int row, int column) {
        if (!(tileInGraph(row, column) && graphVec[row][column] == Empty))
            return false;

        for(int row = 0; row < width ; row++){
            for(int column = 0; column < height; column++){
                if(graphVec[row][column] == Start)
                    graphVec[row][column] = Empty;
            }
        }

        graphVec[row][column] = Start;
        return true;
    }

    bool setFinish(int row, int column) {
        if (!(tileInGraph(row, column) && graphVec[row][column] == Empty))
            return false;

        for(int row = 0; row < width ; row++){
            for(int column = 0; column < height; column++){
                if(graphVec[row][column] == Finish)
                    graphVec[row][column] = Empty;
            }
        }

        graphVec[row][column] = Finish;
        return true;
    }

    vector<vector<spaceTile>> getGraphVec(){
        return graphVec;
    }

    void displayGraph() {
        for (auto i: graphVec) {
            for (auto j: i) {
                switch (j) {
                    case Empty:
                        cout << " [ ] ";
                        break;
                    case Filled:
                        cout << " [#] ";
                        break;
                    case Start:
                        cout << " [S] ";
                        break;
                    case Finish:
                        cout << " [F] ";
                        break;
                }
            }
            cout << endl;
        }
    }
};

void exploreNeighbors(int row, int column, queue<int> &rowQueue, queue<int> &columnQueue, vector<vector<bool>> &visited, Graph graph, int &nodes_left_in_layer, int &nodes_in_next_layer){
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for(int i = 0; i < 4; i++){
        int rr = row + dr[i];
        int cc = column + dc[i];

        // Check if they are inside the matrix
        if(rr < 0 || cc < 0)
            continue;
        if(rr >= graph.getWidth() || cc >= graph.getHeight())
            continue;

        // Check if they're enterable
        if(visited[rr][cc])
            continue;
        if(graph.getGraphVec()[rr][cc] == Filled)
            continue;

        rowQueue.emplace(rr);
        columnQueue.emplace(cc);

        visited[rr][cc] = true;
        nodes_in_next_layer++;
    }
}

tuple<int, int, int> bfs(Graph &graph, int starterRow, int starterColumn) {
    const auto &matrix = graph.getGraphVec();
    vector<vector<bool>> visited(graph.getWidth(), vector<bool>(graph.getHeight(), false));

    int moveCount = 0;
    int nodesLeftInLayer = 1;
    int nodesInNextLayer = 0;

    queue<int> rowQueue;
    queue<int> columnQueue;

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
    return make_tuple(lastRow, lastColumn, moveCount - 1);
}

int getGraphDiameter(Graph &graph){ // It is finding diameter by running bfs 3 times
    int starterRow;
    int starterColumn; // Implement check for if starter isn't blocked

    for (starterRow = 0;  starterRow < graph.getWidth() ; starterRow++) {
        bool tileEmpty = false;
        for (starterColumn = 0; starterColumn < graph.getHeight(); starterColumn++) {
            cout << "starterRow: " << starterRow << ", starterColumn: " << starterColumn << " bool:" << bool(graph.getGraphVec()[starterRow][starterColumn] == Empty) << endl;
            if (graph.getGraphVec()[starterRow][starterColumn] == Empty)
            {
                tileEmpty = true;
                break;
            }
        }
        if(tileEmpty)
            break;
    }

    int firstRow, firstColumn, moveCount;
    tie(firstRow, firstColumn, moveCount) = bfs(graph, starterRow, starterColumn);

    graph.setStart(firstRow, firstColumn);

    // cout << "from first: (" << firstRow << ", " << firstColumn << ") moveCount: " << moveCount << endl;

    int secondRow, secondColumn, diameter;
    tie(secondRow, secondColumn, diameter) = bfs(graph, firstRow, firstColumn);

    graph.setFinish(secondRow, secondColumn);

    // cout << "from second: (" << secondRow << ", " << secondColumn << ") diameter: " << diameter << endl;


    tie(firstRow, firstColumn, diameter) = bfs(graph, secondRow, secondColumn);

    graph.setStart(firstRow, firstColumn);
    cout << "from second: (" << firstRow << ", " << firstColumn << ") diameter: " << diameter << endl;

    return diameter;
}
*/
/*
class pentaminoGraph{
private:
    enum pieceAvailability{
        Used,
        Unused
    };

    int blockCount;

    unordered_map<char, pieceAvailability> pieces = {{'F', Unused},{'I', Unused},{'L', Unused},{'N', Unused},{'P', Unused},{'T', Unused},{'U', Unused},{'V', Unused},{'W', Unused},{'X', Unused},{'Y', Unused},{'Z', Unused},};
public:
    Graph graph;
    pentaminoGraph(int width, int height, int blockCount = 5) : graph(width, height) {
        this->blockCount = blockCount;
        // Constructor body if needed
    }


/*
 * ...
 * .#.
 * .#.
 * .#.
 * .#.
 * .#. DONE
 * ...
 *
 * ....
 * .#..
 * .##.
 * .#.. DONE
 * .#..
 * ....
 *
 * .....
 * .###.
 * .#...
 * .#... DONE
 * .....
 *
 * ....
 * .##.
 * .#.. Done
 * .##.
 * ....
 *
 * ....
 * ..#.
 * .##.
 * .#..Done
 * .#..
 * ....
 *
 * .....
 * ..#..
 * .###. DONE
 * ..#..
 * .....
 *
 *
 *

    bool placePiece(int row, int column, char pieceName){
        unordered_map<char, pair<vector<int>,vector<int>>> pieceSchematics = {
                {'P', {{0, 1, 0, 1, 0},{0,0,1,1,2}}},
                {'I', {{0, 0, 0, 0, 0},{0,1,2,3,4}}},
                {'V', {{0, 0, 0, 1, 2},{0,1,2,0,0}}},
                {'U', {{0, 0, 1, 2, 2},{0,1,0,0,1}}},
                {'X', {{0, 1, 1, 1, 2},{1,0,1,2,1}}},
                {'F', {{0, 0, 1, 1, 2},{1,2,0,1,1}}},
                {'W', {{0, 1, 1, 2, 2},{0,0,1,1,2}}}, // control
                {'T', {{0, 0, 0, 1, 2},{0,1,2,1,1}}},
                {'Y', {{0, 1, 1, 2, 3},{0,0,1,0,0}}},
                {'L', {{0, 0, 1, 2, 3},{0,1,0,0,0}}},
                {'N', {{0, 0, 1, 1, 1},{0,1,1,2,3}}},
                {'Z', {{0, 0, 1, 2, 2},{0,1,1,1,2}}}
        };
        if(placeAnyPiece(row, column, pieceSchematics[pieceName].first, pieceSchematics[pieceName].second))
            cout << "   piece put!!" << endl;

        return true;
    }

    bool placeAnyPiece(int row, int column, vector<int> piecePosX, vector<int> piecePosY){

        bool available = true;

        for(int i = 0; i < blockCount; i++){
            // Check if position is on the graph
            if(row + piecePosX[i] > graph.getWidth() || column + piecePosY[i] > graph.getHeight()){
                //available = false;
                return false;
            }

            // Check if all tiles are empty
            if(graph.getGraphVec()[row + piecePosX[i]][column + piecePosY[i]] == Filled){
                // available = false;
                return false;
            }
        }

        // pieces['F'] = Used; // pieces should be set to used from the other function

        for (int i = 0; i < blockCount; ++i) {
            graph.getGraphVec()[row + piecePosX[row + i]][column + piecePosY[i]] = Filled;
        }

        return true;
    }
};
*/
int main() {


    Graph graph1(5, 5);

    PentaminoGraph pentaminoGraph(7,7);

    int userInputRow = 0, userInputColumn = 0;
    char pieceName;

    while(userInputRow != -1) {
        cout << "Enter piece name" << endl;
        cin >> pieceName;


        cout << "Enter a row" << endl;
        cin >> userInputRow;
        cout << "Enter a column" << endl;
        cin >> userInputColumn;

        /*
        graph1.fillTile(userInputRow, userInputColumn);
        getGraphDiameter(graph1);
        graph1.displayGraph();
        */

        pentaminoGraph.placePiece(userInputRow, userInputColumn, pieceName);
        getGraphDiameter(pentaminoGraph.graph);
        pentaminoGraph.graph.displayGraph();

    }
    return 0;
}

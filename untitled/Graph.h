//
// Created by bryan on 10/15/20.
//

#ifndef GRAPH_H
#define GRAPH_H

#include "Options.h"
#include <iostream>
#include <map>
#include <vector>
#include <climits>

using namespace std;

struct Path {
    vector<int> path; // vector because we don't know the size of the array
    int cost; // total cost to travel path

    Path() : path(), cost(INT_MAX) {} // default constructor
    Path(vector<int> pth, int &cst) : path(pth) , cost(cst) {} // path struct constructor
};

const int NUM_VERTICES_PER_EDGE = 2;

class Graph {
    public:
        Graph(Options options);
        Graph(float **adjacencyMatrix, int numVertices);
        virtual ~Graph();

        void Init();

        pair<int, int>* getVerticesOnEdge(int edgeA); // always returns two vertices

        Path* getShortestPathBetweenVertices(int startVertex, int endVertex);
        Path* getShortestPathBetweenEdges(int edgeA, int edgeB);

        int numVertices;
        int numEdges;
    private:

        map<float, map<float, float>> adjacencyMatrix; // for storing weighted graph

        void calculateNumberOfEdges();
        map<int, map<int, Path>> cachedShortestPaths; // for storing the path results from dijkstra's algorithm
        map<int, map<int, Path>> cachedShortestPathBetweenEdges; // for storing the shortest paths between two edges
        map<int, pair<int, int>> cachedVerticesOnEdge; // for storing the association between edges and vertices

        int minDistance(int dist[], bool sptSet[]);
        void dijkstras(int startVertex);

};


#endif //SRC_GRAPH_H

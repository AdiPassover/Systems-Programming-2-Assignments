// 326627635 | adi.peisach@gmail.com
#include "Graph.hpp"

using namespace std;

void ariel::Graph::initMatrix(vector<vector<int>>* dst, vector<vector<int>> src) {
    (*dst).resize(numVertices);
    for (size_t i = 0; i < numVertices; i++) {
        (*dst)[i].resize(numVertices);
        for (size_t j = 0; j < numVertices; j++) {
            (*dst)[i][j] = src[i][j];
            if (i != j && src[i][j] == 0) (*dst)[i][j] = INF;
        }
    }
}

void ariel::Graph::initParentMatrix() {
    parentMatrix.resize(numVertices);
    for (size_t i = 0; i < numVertices; i++) {
        parentMatrix[i].resize(numVertices);
        for (size_t j = 0; j < numVertices; j++) {
            parentMatrix[i][j] = -1;
            if (adjMatrix[i][j] != INF) { parentMatrix[i][j] = i; }
        }
    }
}

int ariel::Graph::getEdge(size_t start, size_t end) const {
    if (start >= numVertices || end >= numVertices)
        throw out_of_range("Vertex not in graph");
    return adjMatrix[start][end];
}

int ariel::Graph::getDistance(size_t start, size_t end) const {
    if (start >= numVertices || end >= numVertices)
        throw out_of_range("Vertex not in graph");
    return distMatrix[start][end];
}

size_t ariel::Graph::getParent(size_t start, size_t end) const {
    if (start >= numVertices || end >= numVertices)
        throw out_of_range("Vertex not in graph");
    if (parentMatrix[start][end] < 0) return INF;
    return (size_t)parentMatrix[start][end];
}

size_t ariel::Graph::getNumVertices() const { return numVertices; }

bool ariel::Graph::isDirected() const { return directed; }

void ariel::Graph::loadGraph(vector<vector<int>> matrix) {
    numVertices = matrix.size();
    numEdges = 0;

    for (size_t i = 0; i < numVertices; i++) {
        if (numVertices != matrix[i].size())
            throw invalid_argument("Invalid graph: The graph is not a square matrix.");
        if (matrix[i][i] != 0)
            throw invalid_argument("Invalid graph: An edge from a vertex to itself must have 0 weight.");
        for (size_t j = 0; j < matrix.size(); j++) {
            if (matrix[i][j] != 0) numEdges++;
            if (matrix[i][j] == INF || matrix[i][j] == MIN_INF)
                throw invalid_argument("Invalid graph: An edge from a vertex to itself must have 0 weight.");
        }
    }

    bool same = true;
    for (size_t i = 0; i < numVertices; i++) {
        for (size_t j = 0; j < numVertices; j++) {
            if (matrix[i][j] != matrix[j][i]) {
                same = false;
                break;
            }
        }
    }
    directed = !same;

    // Initializing the matrices for Floyd-Warshall
    initMatrix(&adjMatrix, matrix);
    initMatrix(&distMatrix, matrix);
    initParentMatrix();

    // Floyd-Warshall algorithm
    for (size_t k = 0; k < numVertices; k++) {
        for (size_t i = 0; i < numVertices; i++) {
            for (size_t j = 0; j < numVertices; j++) {
                if (distMatrix[i][k] == INF || distMatrix[k][j] == INF) { continue; }
                if (!directed && parentMatrix[i][j] == parentMatrix[k][j]) { continue; }
                if (distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j]) {
                    distMatrix[i][j] = distMatrix[i][k] + distMatrix[k][j];
                    parentMatrix[i][j] = parentMatrix[k][j];
                }
            }
        }
    }

    // Another run of Floyd-Warshall, if we can find shorter paths it means there's a negative cycle.
    for (size_t k = 0; k < numVertices; k++) {
        for (size_t i = 0; i < numVertices; i++) {
            for (size_t j = 0; j < numVertices; j++) {
                if (distMatrix[i][k] == INF || distMatrix[k][j] == INF) { continue; }
                if (distMatrix[i][k] == MIN_INF || distMatrix[k][j] == MIN_INF ||
                           distMatrix[i][j] > distMatrix[i][k] + distMatrix[k][j]) {
                    distMatrix[i][j] = MIN_INF;
                    parentMatrix[i][j] = parentMatrix[k][j];
                }
            }
        }
    }
}

void ariel::Graph::printGraph() const {
    cout << "Graph with " << numVertices << " vertices and " << numEdges << " edges." << endl;
}
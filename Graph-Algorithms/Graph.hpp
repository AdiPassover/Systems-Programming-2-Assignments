// 326627635 | adi.peisach@gmail.com

#include <vector>
#include <stdexcept>
#include <string>
#include <iostream>

const int INF = 2147483647;
const int MIN_INF = -2147483648;

using namespace std;

namespace ariel {

    class Graph {

        /**
         * The number of vertices in the graph.
         */
        size_t numVertices;

        /**
         * The number of edges in the graph.
         */
        size_t numEdges;

        /**
         * Save if the graph is directed or not.
        */
        bool directed;

        /**
         * The graph's adjacency matrix.
         */
        vector<vector<int>> adjMatrix;

        /**
         * distMatrix[i][j] = The shortest path's (least cost) cost from i to j. INF if there isn't, MIN_INF if there's
         * a path from i to j that contains a negative cycle.
         */
        vector<vector<int>> distMatrix;

        /**
         * parentMatrix[i][j] = j's parent in the shortest path (least cost) from i to j. INF if there isn't.
         */
        vector<vector<int>> parentMatrix;
    
    private:

        /**
         * Initializes a matrix with the adjacency matrix. Used to initialize adjMatrix and distMatrix.
         * Should only be used in loadGraph.
         *
         * @param dst The adjacency matrix loaded to the graph.
         * @param src A pointer of the matrix that needs to be initialized.
         */
        void initMatrix(vector<vector<int>>* dst, vector<vector<int>> src);

        /**
         * Initializes parentMatrix with the adjacency matrix.
         * Should only be used in loadGraph.
         */
        void initParentMatrix();

    public:

        /**
         * Load an adjacency matrix into a graph and saves it as adjMatrix and sets numVertices and numEdges to
         * their correct values.
         * Also runs the Floyd-Warshall algorithm and saves the matrices as fields distMatrix and parentMatrix.
         * Note that the adjacency matrix represents a simple graph, which means there is at most one edge from a
         * vertex to another and there are no edges between a vertex and itself. Also, an edge's weight has to be less
         * than the maximum int value and more than the minimal int value.
         * 
         * @param matrix An adjacency matrix
         * @throws invalid_argument If the graph isn't simple or there are weights with illegal values.
        */
        void loadGraph(vector<vector<int>> matrix);

        /**
         * Prints information about a graph using the following format:
         * "Graph with {number of vertices} vertices and {number of edges} edges."
         * Note that in an undirected graph, each edge is considered two edges.
        */
        void printGraph() const;

        /**
         * Get the weight of an edge between two vertices. Returns INF if there's no edge.
         *
         * @param start The starting vertex of the edge
         * @param end The end vertex of the edge
         * @return the weight of the edge or INF if there isn't one
         */
        int getEdge(size_t start, size_t end) const;

        /**
         * Get the shortest path's (least cost) cost between two vertices. Returns INF if there's no path.
         * Returns MIN_INF if there's a path from start to end that contains a negative cycle.
         *
         * @param start The source vertex
         * @param end The destination vertex
         * @return The shortest path cost, INF if there isn't, MIN_INF if there's a negative cycle.
         */
        int getDistance(size_t start, size_t end) const;

        /**
         * Get the parent of end in the shortest path (least cost) between start and end. Returns INF if start and end
         * aren't connected.
         *
         * @param start The source vertex
         * @param end The destination vertex
         * @return The parent of end in the shortest path between start and end, INF if there isn't.
         */
        size_t getParent(size_t start, size_t end) const;

        /**
         * @return the number of vertices in the graph.
         */
        size_t getNumVertices() const;

        /**
         * @return if the graph is connected.
        */
        bool isDirected() const;

    };

}
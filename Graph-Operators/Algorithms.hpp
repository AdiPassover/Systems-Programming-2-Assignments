// 326627635 | adi.peisach@gmail.com
#include "Graph.hpp"
#include <string>
#include <vector>

using namespace std;

namespace ariel {

    enum class State : int {
        Undiscovered = 0,
        Exploring = 1,
        Finished = 2
    };

    class Algorithms {

    private:

        /**
         * Runs DFS on a graph and colors each vertex in a color (0 before coloring, the either 1 or 2)
         * using a color array (color[i] = vertex i's color) and attempts to find a 2-coloring of the graph by coloring
         * a vertex a different color than its neighbour. If it's the same color as another neighbour, it fails and
         * returns false.
         *
         * @param g The graph
         * @param start The starting vertex for DFS
         * @param color A pointer of the vector representing the colors of the vertices (color[i] = vertex i's color)
         * @return true if the graph has a 2-coloring, false otherwise
         */
        static bool DFS_Colors(Graph g, size_t start, vector<int>& color);

        /**
         * Runs DFS on a graph and marks each vertex's state as undiscovered if the algorithm hasn't been there yet,
         * exploring if the algorithm has been there but haven't finished exploring all of its children
         * or finished otherwise. It follows the states using a states array (state[i] = vertex i's state)
         * If the algorithm finds a neighbour marked exploring next to the current vertex it means there's a cycle in
         * the graph and returns a vertex which is part of the cycle. Otherwise returns INF.
         * The function also receives and changes a pointer to a parents vector (parent[i] = vertex i's parent in the
         * DFS forest).
         *
         * @param g The graph
         * @param start The starting vertex for DFS
         * @param state A pointer of  a vector representing the states of the vertices (state[i] = vertex i's state)
         * @param parent A pointer of a vector representing the parents of the vertices (parent[i] = vertex i's parent)
         * @return
         */
        static size_t DFS_Cycle(Graph g, size_t start, vector<State>& state, vector<size_t>& parent);

        /**
         * Trace a cycle in a graph given a starting vertex which is part of the cycle and a vector of the parents of
         * each vertex in the DFS forest.
         * Returns a string representing the cycle with the vertices as numbers and arrows between them.
         *
         * @param start Vertex which is part of the cycle
         * @param parent Vector of the parents of each vertex in the DFS forest.
         * @return A string representing the cycle.
         */
        static string traceCycle(size_t start, vector<size_t> parent);

        /**
         * Trace a negative cycle in a graph given a starting vertex which is part of the cycle using the parent matrix
         * from floyd-warshall.
         * Returns a string representing the cycle with the vertices as numbers and arrows between them.
         *
         * @param start a starting vertex which is part of the cycle
         * @param parent a vector of the parents of each vertex in the DFS forest.
         * @return A string representing the cycle.
         * @throws invalid_argument If the graph doesn't have a negative cycle with the vertex start.
         */
        static string traceNegativeCycle(Graph g, size_t start);

    public:
        
        /**
         * Checks if a graph is strongly connected.
         * For undirected graph, cheks if the graph is connected.
         *
         * @param g The graph
         * @return true if g is strongly connected, false otherwise
         */
        static bool isConnected(Graph g);

        /**
         * Finds the shortest path (with the least cost) from a vertex to another.
         * Returns a string representing the path with the vertices as numbers and arrows between them.
         * Returns "No shortest path because the vertices aren't connected." if the vertices aren't connected.
         * Returns "No shortest path because graph has negative cycle." if there's a path from start to end that
         * contains a negative cycle.
         * Note that in a simple graph the shortest path from a vertex to itself is 0 unless it's connected to a
         * negative cycle, then it's MIN_INF.
         *
         * @param g The graph
         * @param start The source vertex
         * @param end The destination vertex
         * @return A string representing the path or the reason there isn't one
         */
        static string shortestPath(Graph g, size_t start, size_t end);

        /**
         * Checks if there's a cycle in a graph using the function DFS_Cycle. If there are, return one of them using
         * the function traceCycle.
         * Returns a string representing the cycle with the vertices as numbers and arrows between them.
         * Returns "No cycles in graph." in case there are no cycles.
         *
         * @param g The graph
         * @return A string representing the cycle or "No cycles in graph."
         */
        static string isContainsCycle(Graph g);

        /**
         * Checks if the graph is bipartite by trying to find a 2-coloring of it (we proved that graph has a 2-coloring
         * iff it's bipartite) using the function DFS_Colors.
         * If it is, returns a string representing the two disjoint sets.
         * If it isn't, returns "The graph isn't bipartite.".
         *
         * @param g The graph
         * @return a string representing the two disjoint sets or "The graph isn't bipartite."
         */
        static string isBipartite(Graph g);

        /**
         * Checks if there's a negative cycle in a graph. If there are, return one of them using traceNegativeCycle.
         * Returns a string representing the negative cycle with the vertices as numbers and arrows between them.
         * Returns "No negative cycles." in case there are no cycles.
         *
         * @param g The graph
         * @return A string representing the cycle or "No negative cycles."
         */
        static string negativeCycle(Graph g);

    };

}
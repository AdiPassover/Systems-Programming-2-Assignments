326627635 | adi.peisach@gmail.com

**Systems Programming 2 - Assignment 1**

This is a C++ program that gives infromation about simple graphs based on adjacency matrices.
Note that the adjacency matrix represents a simple graph, which means there is at most one edge from a vertex to another and there are no edges between a vertex and itself. Also, an edge's weight has to be an integer less than the maximum int value and more than the minimal int value.


**Instructions**

1. Write an adjacency matrix as a vector of vectors of ints that represents a simple graph and 0 means no edge.
2. Initiazlie a Graph object and use the loadGraph function to load the matrix to the graph.
3. Use whichever function you want from the Algorithms class (or printGraph from Graph)
4. If you want information about a different graph, you can initialize another graph or load another matrix to an existing graph.


**The Program**

The program is separated into 2 main classes: Graph and Algorithms.
When loading a graph using loadGraph, it loads an adjacency matrix into a graph and saves it as adjMatrix where INF (max int) means no edge, and sets numVertices and numEdges to their correct values. Also runs the Floyd-Warshall algorithm twice (the second time for finding negative cycles) and saves the matrices as fields distMatrix and parentMatrix for later algorithms.
Note that according to wikipedia (https://en.wikipedia.org/wiki/Floyd%E2%80%93Warshall_algorithm):
"Obviously, in an undirected graph a negative edge creates a negative cycle (i.e., a closed walk) involving its incident vertices."
This is why, when looking for a shortest path it is allowed to go back and forth on an edge, and a negative edge in an undirected graph is considered a negaitve cycle.
After loading a graph, you can print int using printGraph and get the information about the number of edges and vertices, or use a function from the Algorithms class:

        /**
         * Checks if a graph is strongly connected.
         * For undirected graph, cheks if the graph is connected.
         *
         * @param g The graph
         * @return true if g is strongly connected, false otherwise
         */
        static bool isConnected(Graph g);
        
This function uses the distMatrix (from FW) in order to find if there's a path from each vertx to each vertex.
        
        
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
        
 This function uses the parentMatrix (from FW) in order to trace the vertices of the shortest path.
        
        
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
        
This function uses a helper function - DFS_Cycle, that runs DFS and marks each vertex's state as undiscovered, exploring or finished. If the algorithm finds a neighbour marked exploring next to the current vertex it means there's a cycle and ir returns a vertex from the cycle and the fucntion traces the cycle using the parent vector from the DFS forest using the helper function - traceCycle.
        
        
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
        
This function uses a helper function - DFS_Colors, that runs DFS on a graph and colors each vertex in a color and attempts to find a 2-coloring of the graph by coloring a vertex a different color than its neighbour. If it's the same color as another neighbour, it fails and returns false. Then the function uses the colors to find the 2 disjoint sets in the graph.
        
        
        /**
         * Checks if there's a negative cycle in a graph. If there are, return one of them using traceNegativeCycle.
         * Returns a string representing the negative cycle with the vertices as numbers and arrows between them.
         * Returns "No negative cycles." in case there are no cycles.
         *
         * @param g The graph
         * @return A string representing the cycle or "No negative cycles."
         */
        static string negativeCycle(Graph g);
        
This function uses the distMatrix (from FW) and serches from negative paths from a vertex to itself, which means there's a negative cycle. Then, it traces the the negative cycles using traceNegativeCycle which uses the parentMatrix (from FW), because the shortest path has to contain the negative cycle.
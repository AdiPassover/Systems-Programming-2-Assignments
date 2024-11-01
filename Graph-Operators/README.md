326627635 | adi.peisach@gmail.com

# Systems Programming 2 - Assignment 2

This is a C++ program that gives information about simple graphs based on adjacency matrices.
Note that the adjacency matrix represents a simple graph, which means there is at most one edge from a vertex to another and there are no edges between a vertex and itself. Also, an edge's weight has to be an integer less than the maximum int value and more than the minimal int value.


**Instructions**

1. Write an adjacency matrix as a vector of vectors of ints that represents a simple graph and 0 means no edge.
2. Initialize a Graph object and use the loadGraph function to load the matrix to the graph.
3. Repeat this process to initialize as many graphs as you want.
4. Use any operators you want on the graphs whichever function you want from the Algorithms class (or printGraph from Graph).


**The Program**

The operators are declared in "GraphOperations.cpp", and the implementation of the operators are in "GraphOperations.cpp".
The supported operations are:

        Graph + Graph
        Graph += Graph
Sums the weight of each edge with the appropriate edge from the second graph. If there's no edge, the weight is 0. If the sum is 0, there won't be an edge in the new graph.

        Graph - Graph
        Graph -= Graph
Subtract the weight of each edge from the second from the appropriate edge from the first graph. If there's no edge, the weight is 0. If the difference is 0, there won't be an edge in the new graph.

        Graph * Graph
        Graph *= Graph
Multiplies the adjacency matrices of the graphs and then deletes edges from a vertex to itself to get a new adjacency matrix for a new graph. If there's no edge, its weight is 0. If a cell is 0, there won't be an edge there in the new graph.


        Graph + int
        Graph += int
Adds an integer to the weight of each edge. If the sum is 0 the edge will be deleted. Non existent won't be affected.

        Graph - int
        Graph -= int
Subtracts an integer from the weight of each edge. If the difference is 0 the edge will be deleted. Non existent won't be affected.

        Graph * int
        Graph *= int
Multiplies an integer with the weight of each edge. If the result is 0 the edge will be deleted. Non existent won't be affected.

        Graph / int
        Graph /= int
Divides an integer from the weight of each edge. If the result is 0 the edge will be deleted. Non existent won't be affected. Dividing by 0 will throw an error.

        Graph++
        ++Graph
Adds 1 to the graphs (as mentioned above).

        Graph--
        --Graph
Subtructs 1 from the graphs (as mentioned above).


        Graph < Graph
        Graph > Graph
For graphs A and B, A>B iff A contains B's adjacent matrix but isn't equals to it, or if A has more edges than B, or if A and B have the same number of edges and A has more vertices than B.

        Graph == Graph
        Graph != Graph
Graphs A and B are equal iff they have the same adjacency matrix or if A>B returns false and B<A returns false.

        Graph <= Graph
        Graph >= Graph
Returns if a graph is greater or equal to another graph.

The tests for the operators are in TestOperations.cpp and there are also test for using operators on graphs and then using algorithms. There are also examples in Demo.cpp.

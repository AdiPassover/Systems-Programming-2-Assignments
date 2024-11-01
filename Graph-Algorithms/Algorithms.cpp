// 326627635 | adi.peisach@gmail.com
#include "Algorithms.hpp"

bool ariel::Algorithms::isConnected(Graph g) {
    for (size_t i = 0; i < g.getNumVertices(); i++) {
        for (size_t j = 0; j < g.getNumVertices(); j++) {
            if (g.getDistance(i,j) == INF) return false;
        }
    }
    return true;
}

string ariel::Algorithms::shortestPath(Graph g, size_t start, size_t end) {
    if (g.getDistance(start,end) == INF) return "No shortest path because the vertices aren't connected.";
    if (g.getDistance(start,end) == MIN_INF) return "No shortest path because graph has negative cycle.";

    size_t parent = g.getParent(start,end);
    string ans = "->" + to_string(end);
    while (parent != start) { // Trace back the shortest path using the parent matrix until we get to the source
        string curr = "->" + to_string(parent);
        ans = curr + ans;
        parent = g.getParent(start,parent);
    }
    ans = to_string(start) + ans;
    return ans;
}

string ariel::Algorithms::isContainsCycle(Graph g) {
    vector<State> state(g.getNumVertices(), ariel::State::Undiscovered);
    vector<size_t> parent(g.getNumVertices(), INF);

    // Run DFS from every vertex that hasn't been found by previous DFSs
    for (size_t s = 0; s < g.getNumVertices(); s++) {
        if (state[s] != ariel::State::Undiscovered) continue;
        state[s] = ariel::State::Exploring;
        size_t v = DFS_Cycle(g,s,state,parent);
        if (v != INF) // if DFS found a cycle, trace it
            return traceCycle(v,parent);
    }

    return "No cycles in graph.";
}

size_t ariel::Algorithms::DFS_Cycle(Graph g, size_t start, vector<State>& state, vector<size_t>& parent) {
    // for each of start's neighbours:
    for (size_t v = 0; v < g.getNumVertices(); v++) {
        if (start == v || g.getEdge(start,v) == INF) continue;
        if (!g.isDirected() && parent[start] == v) continue;
        if (state[v] == ariel::State::Exploring) { // If we are currently exploring a neighbour, this is a cycle.
            parent[v] = start;
            return v;
        }
        if (state[v] == ariel::State::Undiscovered) {
            parent[v] = start;
            state[v] = ariel::State::Exploring;
            size_t ans = DFS_Cycle(g,v,state,parent);
            if (ans != INF) return ans;
        }
    }
    state[start] = ariel::State::Finished;
    return INF;
}

string ariel::Algorithms::traceCycle(size_t start, vector<size_t> parent) {
    string ans = "->" + to_string(start);
    size_t pre = parent[start];
    while (pre != start) { // Trace back the cycle using the parents from DFS until we get to the source
        string curr = "->" + to_string(pre);
        ans = curr + ans;
        pre = parent[pre];
    }
    return to_string(start) + ans;
}

string ariel::Algorithms::isBipartite(Graph g) {
    vector<int> color(g.getNumVertices(), 0);

    for (size_t i = 0; i < g.getNumVertices(); i++) {
        if (color[i] != 0) continue;

        // Choose starting color different from adjacent vertices.
        for (size_t j = 0; j < g.getNumVertices(); j++) {
            if (i!=j && (g.getEdge(i,j) != INF || g.getEdge(j,i) != INF) && color[j] != 0) {
                color[i] = 3-color[j];
                break;
            }
        }
        if (color[i] == 0) { color[i] = 1; } // If there are no colored neighbours, color it 1

        if (!DFS_Colors(g,i,color)) return "The graph isn't bipartite.";
    }

    // If there's a 2-Coloring, find the set of each color. Those are the 2 disjoint sets of the bipartite graph.
    string ans = "The graph is bipartite: A={";
    bool first = true;
    for (size_t i = 0; i < g.getNumVertices(); i++) { // add to A all the vertices with color 1.
        if (color[i] == 1) {
            if (first) { first = false; }
            else { ans.append(","); }
            ans.append(to_string(i));
        }
    }
    ans.append("}, B={");
    first = true;
    for (size_t i = 0; i < g.getNumVertices(); i++) { // add to B all the vertices with color 1.
        if (color[i] == 2) {
            if (first) { first = false; }
            else { ans.append(","); }
            ans.append(to_string(i));
        }
    }
    return ans.append("}");
}

bool ariel::Algorithms::DFS_Colors(Graph g, size_t start, vector<int>& color) {
    // For each of start's neighbours:
    for (size_t v = 0; v < g.getNumVertices(); v++) {
        if (start == v || g.getEdge(start,v) == INF) continue;
        if (color[v] == color[start]) return false; // If a neighbour has the same color, the 2-coloring failed
        if (color[v] == 0) {
            color[v] = 3-color[start]; // Color the neighbour a different color than start
            if (!DFS_Colors(g,v,color)) return false;
        }
    }
    return true;
}

string ariel::Algorithms::negativeCycle(Graph g) {
    for (size_t v = 0; v < g.getNumVertices(); v++) {
        // If there's a negative path from a vertex to itself, there's a negative cycle.
        if (g.getDistance(v,v) < 0)
            return traceNegativeCycle(g,v);
    }
    return "No negative cycles.";
}

string ariel::Algorithms::traceNegativeCycle(Graph g, size_t start) {
    // save the shortest path from start to start in order to find the negative cycle in it.
    vector<size_t> path(g.getNumVertices()+1,INF);
    path[0] = start;
    path[1] = g.getParent(start,start);

    for (size_t i = 2; i < g.getNumVertices()+1; i++) {
        path[i] = g.getParent(start,path[i-1]);
        for (size_t j = 0; j < i; j++) { // check the path to see if we've already been to this vertex.
            if (path[i] != path[j]) { continue; }
            string ans = to_string(path[i]).append("->");
            while (1) { // If we have, we've found the negative cycle and build it from the path vector.
                i--;
                ans.append(to_string(path[i]));
                if (i == j) { return ans; }
                ans.append("->");
            }
        }
    }
    throw invalid_argument("Called traceNegativeCycle without negative cycles from the starting vertex.");
}
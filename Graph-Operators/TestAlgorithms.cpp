// 326627635 | adi.peisach@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"

using namespace std;


/**
 * Checks if a string representing a cycle is actually a cycle in the graph.
 *
 * @param g The graph in which the cycle may be
 * @param cycle A string representing a negative cycle
 */
bool checkCycle(ariel::Graph g, string cycle) {
    size_t idx = cycle.find("->");
    if (idx == string::npos) { return false; }
    size_t start = (size_t)stoi(cycle.substr(0,idx));
    size_t startCopy = start;
    cycle.erase(0,idx+2);

    idx = cycle.find("->");
    while (idx != string::npos) {
        size_t vertex = (size_t)stoi(cycle.substr(0,idx));
        if (g.getEdge(start,vertex) == INF) return false;
        cycle.erase(0,idx+2);

        idx = cycle.find("->");
        start = vertex;
    }
    size_t last = (size_t)stoi(cycle);
    if (g.getEdge(start,last) == INF) return false;
    return last == startCopy;
}

/**
 * Checks if a string representing a cycle is actually a negative cycle in the graph.
 *
 * @param g The graph in which the cycle may be
 * @param cycle A string representing a negative cycle
 */
bool checkNegativeCycle(ariel::Graph g, string cycle) {
    int sum = 0;
    size_t idx = cycle.find("->");
    if (idx == string::npos) { return false; }
    size_t start = (size_t)stoi(cycle.substr(0,idx));
    size_t startCopy = start;
    cycle.erase(0,idx+2);

    idx = cycle.find("->");
    while (idx != string::npos) {
        size_t vertex = (size_t)stoi(cycle.substr(0,idx));
        if (g.getEdge(start,vertex) == INF) return false;
        sum += g.getEdge(start,vertex);
        cycle.erase(0,idx+2);

        idx = cycle.find("->");
        start = vertex;
    }
    size_t last = (size_t)stoi(cycle);
    if (g.getEdge(start,last) == INF) return false;
    sum += g.getEdge(start,last);
    return last == startCopy && sum < 0;
}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph3 = {{0, -1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 1, -4, 4, 0, 0, 0, 0,},
                                  {3, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 2, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, -7, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1,},
                                  {0, 0, 0, 0, 0, 2, 0, 0, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph4 = {{0, -1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 1, -4, 4, 1, 0, 0, 0,},
                                  {3, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 2, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 1, 0, 0, 0, 0, -7, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1,},
                                  {0, 0, 0, 0, 0, 2, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isConnected(g) == false);

    vector<vector<int>> graph5 = {{0, -1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 1, -4, 4, 1, 0, 0, 0,},
                                  {3, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 2, 0, 0, 0, 0,},
                                  {0, 1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 1, 0, 0, 0, 0, -7, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1,},
                                  {0, 0, 0, 0, 0, 2, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph6 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                   {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "No shortest path because the vertices aren't connected.");

    vector<vector<int>> graph3 =
            {{0, 7, 3, 1, 0},
             {0, 0, 0, -4, -4},
             {2, -1, 0, 0, 0},
             {0, 0, 8, 0, 0},
             {0, 0, 0, 3, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "0->2->1");
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0->2->1->4");
    CHECK(ariel::Algorithms::shortestPath(g, 3, 1) == "3->2->1");
    CHECK(ariel::Algorithms::shortestPath(g, 3, 4) == "3->2->1->4");
    CHECK(ariel::Algorithms::shortestPath(g, 2, 1) == "2->1");

    vector<vector<int>> graph6 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 1) == "No shortest path because graph has negative cycle.");
    CHECK(ariel::Algorithms::shortestPath(g, 9, 8) == "No shortest path because graph has negative cycle.");
    CHECK(ariel::Algorithms::shortestPath(g, 9, 6) == "9->4->5->6");
    CHECK(ariel::Algorithms::shortestPath(g, 1, 2) == "No shortest path because graph has negative cycle.");
    CHECK(ariel::Algorithms::shortestPath(g, 3, 2) == "No shortest path because graph has negative cycle.");
    CHECK(ariel::Algorithms::shortestPath(g, 5, 1) == "No shortest path because the vertices aren't connected.");
    CHECK(ariel::Algorithms::shortestPath(g, 9, 7) == "9->4->7");
}
TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(checkCycle(g,ariel::Algorithms::isContainsCycle(g)));

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(checkCycle(g,ariel::Algorithms::isContainsCycle(g)));

    vector<vector<int>> graph4 = {{0, -1, 0, 0, 0},
                                  {0, 0, 1, -4, 4},
                                  {3, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 2},
                                  {0, 1, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(checkCycle(g,ariel::Algorithms::isContainsCycle(g)));

    vector<vector<int>> graph5 = {{0, -1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 1, -4, 4, 0, 0, 0, 0,},
                                  {3, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 2, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, -7, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1,},
                                  {0, 0, 0, 0, 0, 2, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(checkCycle(g,ariel::Algorithms::isContainsCycle(g)));

    vector<vector<int>> graph6 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(checkCycle(g,ariel::Algorithms::isContainsCycle(g)));

    vector<vector<int>> graph7 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycles in graph.");

    vector<vector<int>> graph8 = {{0, 0, -1, 0, 1, 0},
                                  {123, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 21, -200, 7},
                                  {0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0}};
    g.loadGraph(graph8);
    CHECK(ariel::Algorithms::isContainsCycle(g) == "No cycles in graph.");
}
TEST_CASE("Test isBipartite")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2}, B={1}");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");

    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");

    vector<vector<int>> graph4 = {
            {0, -1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 4, 0, 0, 0, 0},
            {0, 23, 0, 0, -3, 0, 4, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2,3,5,7}, B={1,4,6}");

    vector<vector<int>> graph5 = {
            {0, -1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
            {0, 23, 0, 0, -3, 0, 4, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, -1, 0}};
    g.loadGraph(graph5);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0,2,3,5,7,8}, B={1,4,6,9}");

    vector<vector<int>> graph6 = {
            {0, -1, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
            {0, 23, 0, 0, -3, 0, 4, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 2, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, -1, 0}};
    g.loadGraph(graph6);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph isn't bipartite.");

}

TEST_CASE("Test negativeCycle") {
    ariel::Graph g;
    vector<vector<int>> graph1 = {
            {0, 1, -2, 0, 0},
            {1, 0, 3, 0, 0},
            {2, 3, 0, 4, 0},
            {0, 0, 4, 0, 5},
            {0, 0, 0, 5, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycles.");

    vector<vector<int>> graph2 = {
            {0, -1, 0},
            {0, 0, -1},
            {1, 0, 0}};
    g.loadGraph(graph2);
    CHECK(checkNegativeCycle(g,ariel::Algorithms::negativeCycle(g))); // "0->1->2->0"

    vector<vector<int>> graph3 = {
            {0, -2, 6, 0},
            {3, 0, 1, 0},
            {1, 0, 0, -1},
            {1, 2, 0, 0}};
    g.loadGraph(graph3);
    CHECK(checkNegativeCycle(g,ariel::Algorithms::negativeCycle(g))); // "0->1->2->3->0"

    vector<vector<int>> graph4 = {{0, -1, 0, 0, 0},
                                  {0, 0, 1, -4, 4},
                                  {3, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 2},
                                  {0, 1, 0, 0, 0}};
    g.loadGraph(graph4);
    CHECK(checkNegativeCycle(g,ariel::Algorithms::negativeCycle(g)));

    vector<vector<int>> graph5 = {{0, -1, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 1, -4, 4, 0, 0, 0, 0,},
                                  {3, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 2, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, -7, 0, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0,},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1,},
                                  {0, 0, 0, 0, 0, 2, 0, 0, 0}};
    g.loadGraph(graph5);
    CHECK(checkNegativeCycle(g,ariel::Algorithms::negativeCycle(g)));

    vector<vector<int>> graph6 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph6);
    CHECK(checkNegativeCycle(g,ariel::Algorithms::negativeCycle(g)));

    vector<vector<int>> graph7 = {{0, 0, 0, -2, 0, 0, 0, 0, 0, 0},
                                  {-2, 0, 1, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                                  {0, 50, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 4, 0, -1, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 2, 0, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
                                  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                                  {0, 1, 0, 0, 3, 0, 0, 0, 0, 0}};
    g.loadGraph(graph7);
    CHECK(ariel::Algorithms::negativeCycle(g) == "No negative cycles.");
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));

    ariel::Graph g1;
    vector<vector<int>> graph1 = {
            {0,1,1},
            {1,1,3},
            {0,1,0}};
    CHECK_THROWS(g1.loadGraph(graph1));

    ariel::Graph g2;
    vector<vector<int>> graph2 = {
            {0,1,1},
            {1,0,3},
            {0,1,0,1}};
    CHECK_THROWS(g2.loadGraph(graph2));

    ariel::Graph g3;
    vector<vector<int>> graph3 = {
            {0,1,MIN_INF},
            {1,0,3},
            {0,1,0,1}};
    CHECK_THROWS(g3.loadGraph(graph3));

    ariel::Graph g4;
    vector<vector<int>> graph4 = {
            {0,1,INF},
            {1,0,3},
            {0,1,0,1}};
    CHECK_THROWS(g4.loadGraph(graph4));

    ariel::Graph g5;
    vector<vector<int>> graph5 = {
            {0,1,1},
            {1,0,3},
            {0,1,0}};
    g5.loadGraph(graph5);
    CHECK_THROWS(g5.getEdge(0,3));
    CHECK_THROWS(g5.getParent(4,2));
    CHECK_THROWS(g5.getDistance(4,3));
}

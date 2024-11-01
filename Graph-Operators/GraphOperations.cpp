// 326627635 | adi.peisach@gmail.com

#include <ostream>
#include "GraphOperations.hpp"
#include "Graph.hpp"

std::ostream& ariel::operator<<(std::ostream& os, const Graph& g) {
    os << g.printGraph() << endl;
    return os;
}

ariel::Graph ariel::operator+(const Graph& left, const Graph& right) {
    if (left.getNumVertices() != right.getNumVertices())
        throw std::invalid_argument("Can only do addition to graphs with the same number of vertices");
    size_t n = left.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            int e1 = left.getEdge(i,j);
            if (e1 == INF) { e1 = 0; }
            int e2 = right.getEdge(i,j);
            if (e2 == INF) { e2 = 0; }
            matrix[i][j] = e1 + e2;
        }
    }

    Graph result;
    result.loadGraph(matrix);
    return result;
}

ariel::Graph ariel::operator-(const Graph& left, const Graph& right) {
    if (left.getNumVertices() != right.getNumVertices())
        throw std::invalid_argument("Can only do subtraction to graphs with the same number of vertices");
    size_t n = left.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            int e1 = left.getEdge(i,j);
            if (e1 == INF) { e1 = 0; }
            int e2 = right.getEdge(i,j);
            if (e2 == INF) { e2 = 0; }
            matrix[i][j] = e1 - e2;
        }
    }

    Graph result;
    result.loadGraph(matrix);
    return result;
}

ariel::Graph ariel::operator*(const Graph& left, const Graph& right) {
    if (left.getNumVertices() != right.getNumVertices())
        throw std::invalid_argument("The number of columns in the first matrix must be equal to the number of rows in the second matrix.");
    size_t n = left.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;
            for (size_t k = 0; k < n; k++) {
                int e1 = left.getEdge(i,k);
                if (e1 == INF) { e1 = 0; }
                int e2 = right.getEdge(k,j);
                if (e2 == INF) { e2 = 0; }
                matrix[i][j] += e1 * e2;
            }
        }
    }

    Graph result;
    result.loadGraph(matrix);
    return result;
}


ariel::Graph& ariel::operator+=(Graph& left, const Graph& right) {
    left = left + right;
    return left;
}

ariel::Graph& ariel::operator-=(Graph& left, const Graph& right) {
    left = left - right;
    return left;
}

ariel::Graph& ariel::operator*=(Graph& left, const Graph& right) {
    left = left * right;
    return left;
}


ariel::Graph ariel::operator+(const Graph& g, int scalar) {
    size_t n = g.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (i == j) continue;
            int edge = g.getEdge(i,j);
            if (edge == INF) { continue; }
            matrix[i][j] = edge + scalar;
        }
    }
    Graph result;
    result.loadGraph(matrix);
    return result;
}

ariel::Graph ariel::operator-(const Graph& g, int scalar) {
    return g + (scalar*-1);
}

ariel::Graph ariel::operator*(const Graph& g, int scalar) {
    size_t n = g.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            int edge = g.getEdge(i,j);
            if (edge == INF) { edge = 0; }
            matrix[i][j] = edge * scalar;
        }
    }
    Graph result;
    result.loadGraph(matrix);
    return result;
}

ariel::Graph ariel::operator/(const Graph& g, int scalar) {
    if (scalar == 0) { throw std::runtime_error("Can't divide by 0"); }
    size_t n = g.getNumVertices();
    vector<vector<int>> matrix(n, vector<int>(n,0));
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            int edge = g.getEdge(i,j);
            if (edge == INF) { edge = 0; }
            matrix[i][j] = edge / scalar;
        }
    }
    Graph result;
    result.loadGraph(matrix);
    return result;
}


ariel::Graph& ariel::operator+=(Graph& g, int scalar) {
    g = g + scalar;
    return g;
}

ariel::Graph& ariel::operator-=(Graph& g, int scalar) {
    g = g - scalar;
    return g;
}

ariel::Graph& ariel::operator*=(Graph& g, int scalar) {
    g = g * scalar;
    return g;
}

ariel::Graph& ariel::operator/=(Graph& g, int scalar) {
    g = g / scalar;
    return g;
}


ariel::Graph& ariel::operator++(Graph& graph) { // ++Graph
    graph += 1;
    return graph;
}

ariel::Graph ariel::operator++(Graph& graph, int) { // Graph++
    graph += 1;
    return graph - 1;
}

ariel::Graph& ariel::operator--(Graph& graph) { // --Graph
    graph -= 1;
    return graph;
}

ariel::Graph ariel::operator--(Graph& graph, int) { // Graph--
    graph -= 1;
    return graph + 1;
}

ariel::Graph ariel::operator+(const Graph& graph) { // +Graph
    return graph;
}

ariel::Graph ariel::operator-(const Graph& graph) { // -Graph
    return graph * -1;
}

bool equalsMatrix(ariel::Graph g1, size_t row, size_t col, ariel::Graph g2) {
    size_t n = g1.getNumVertices();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            if (g1.getEdge(i,j) != g2.getEdge(row+i,col+j))
                return false;
        }
    }
    return true;
}

bool ariel::operator<(const Graph& left, const Graph& right) {
    if (right.getNumVertices() > left.getNumVertices()) {
        size_t diff = right.getNumVertices() - left.getNumVertices();
        for (size_t i = 0; i <= diff; i++) {
            for (size_t j = 0; j <= diff; j++) {
                if (equalsMatrix(left,i,j,right)) return true; // right contains left and doesn't equal left
            }
        }
    }

    if (left.getNumEdges() < right.getNumEdges()) return true;
    if (left.getNumEdges() > right.getNumEdges()) return false;
    return right.getNumVertices() > left.getNumVertices();
}

bool ariel::operator>(const Graph& left, const Graph& right) {
    return right < left;
}

bool ariel::operator==(const Graph& left, const Graph& right) {
    if (left.getNumVertices() != right.getNumVertices())
        return !(left > right || left < right);

    if (equalsMatrix(left,0,0,right)) return true;
    
    return !(left > right || left < right);
}

bool ariel::operator<=(const Graph& left, const Graph& right) {
    return left < right || left == right;
}

bool ariel::operator>=(const Graph& left, const Graph& right) {
    return left > right || left == right;
}

bool ariel::operator!=(const Graph& left, const Graph& right) {
    return !(left == right);
}
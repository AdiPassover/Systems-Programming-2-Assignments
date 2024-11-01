// 326627635 | adi.peisach@gmail.com

namespace ariel {
    class Graph;

    // ostream << Graph
    std::ostream& operator<<(std::ostream& os, const Graph& graph);

    // +Graph
    Graph operator+(const Graph& graph);
    // -Graph
    Graph operator-(const Graph& graph);

    // Graph + Graph
    Graph operator+(const Graph& left, const Graph& right);
    // Graph - Graph
    Graph operator-(const Graph& left, const Graph& right);
    // Graph * Graph
    Graph operator*(const Graph& left, const Graph& right);

    // Graph += Graph
    Graph& operator+=(Graph& left, const Graph& right);
    // Graph -= Graph
    Graph& operator-=(Graph& left, const Graph& right);
    // Graph *= Graph
    Graph& operator*=(Graph& left, const Graph& right);

    // Graph + int
    Graph operator+(const Graph& left, int scalar);
    // Graph - int
    Graph operator-(const Graph& left, int scalar);
    // Graph * int
    Graph operator*(const Graph& left, int scalar);
    // Graph / int
    Graph operator/(const Graph& left, int scalar);

    // Graph += int
    Graph& operator+=(Graph& left, int scalar);
    // Graph -= int
    Graph& operator-=(Graph& left, int scalar);
    // Graph *= int
    Graph& operator*=(Graph& left, int scalar);
    // Graph /= int
    Graph& operator/=(Graph& left, int scalar);

    // ++Graph
    Graph& operator++(Graph& graph);
    // Graph++
    Graph operator++(Graph& graph, int);
    // --Graph
    Graph& operator--(Graph& graph);
    // Graph--
    Graph operator--(Graph& graph, int);

    // Graph < Graph
    bool operator<(const Graph& left, const Graph& right);
    // Graph > Graph
    bool operator>(const Graph& left, const Graph& right);
    // Graph <= Graph
    bool operator<=(const Graph& left, const Graph& right);
    // Graph >= Graph
    bool operator>=(const Graph& left, const Graph& right);
    // Graph == Graph
    bool operator==(const Graph& left, const Graph& right);
    // Graph != Graph
    bool operator!=(const Graph& left, const Graph& right);

}
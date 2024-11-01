#ifndef TREE_ITERATORS_NODE
#define TREE_ITERATORS_NODE
#include <vector>
#include <stdexcept>
#include <iostream>

using std::vector;

template <typename T>
class Node {
    T value;
    vector<Node<T>*> children;
    unsigned int maxDeg = 0;
    unsigned int currChild = 0;

public:
    Node(T value) : value(value) { children.resize(0); }
    Node(T value, unsigned int degree) : value(value) { setDegree(degree); }
    ~Node() {
        for (auto& child : children)
            delete child;
        children.clear();
    }

    void setDegree(unsigned int degree);
    T getValue() const { return value; }

    void addChild(Node<T>* child);
    unsigned int numChildren() const { return currChild; }
    Node<T>* getChild(unsigned int index) const { return children[index]; }

    T operator*() const { return value; }

    class Iterator {
        vector<Node<T>*>* childrenIterator;
        size_t index;
    public:
        explicit Iterator(vector<Node<T>*>* c, size_t index = 0) : childrenIterator(c), index(index) {}

        Iterator& operator++() {
            ++index;
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return index != other.index;
        }

        Node<T>& operator*() const {
            return *(*childrenIterator)[index];
        }
    };

    Iterator begin() {
        return Iterator(&children);
    }

    Iterator end() {
        return Iterator(&children, currChild);
    }
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
    os << node.getValue();
    return os;
}

template<typename T>
void Node<T>::addChild(Node<T>* child) {
    if (currChild >= maxDeg)
        throw std::out_of_range("The node has reached its maximum degree");
    children[currChild++] = child;
}

template<typename T>
void Node<T>::setDegree(unsigned int degree) {
    if (maxDeg != 0)
        throw std::logic_error("The degree of the node has already been set");
    maxDeg = degree;
    children.resize(degree);
}

#endif // TREE_ITERATORS_NODE

#ifndef TREE_ITERATORS_TREE
#define TREE_ITERATORS_TREE

#include "Node.cpp"
#include <queue>
#include <algorithm>

template <typename T, unsigned int D = 2>
class Tree {
private:
    Node<T>* root = nullptr;

public:
    ~Tree() { delete root; }

    void addRoot(T nodeValue);
    void addSubNode(T parentValue, T childValue);

    Node<T>* getRoot() const { return root; }
    unsigned int getDegree() const { return D; }

    class TreeIterator {
    protected:
        std::queue<Node<T>*> nodeQueue;
    public:

        virtual TreeIterator& operator++() {
            nodeQueue.pop();
            return *this;
        }

        virtual bool operator!=(const TreeIterator& other) const {
            return !nodeQueue.empty() || !other.nodeQueue.empty();
        }

        virtual Node<T>& operator*() const {
            return *nodeQueue.front();
        }
    };

    class BFSIterator : public TreeIterator {
    public:
        explicit BFSIterator(Node<T>* root = nullptr) : TreeIterator() {
            if (root != nullptr)
                visitBFS(root);
        }

        void visitBFS(Node<T>* source) {
            std::queue<Node<T>*> q;
            q.push(source);
            while (!q.empty()) {
                Node<T>* node = q.front();
                this->nodeQueue.push(node);
                q.pop();
                for (auto& child : *node)
                    q.push(&child);
            }
        }
    };

    class PreOrderIterator : public TreeIterator {
    public:
        explicit PreOrderIterator(Node<T>* root = nullptr) : TreeIterator() {
            if (root != nullptr)
                visitPreOrder(root);
        }

        void visitPreOrder(Node<T>* node) {
            this->nodeQueue.push(node);
            for (auto& child : *node)
                visitPreOrder(&child);
        }

    };

    class PostOrderIterator : public TreeIterator {
    public:
        explicit PostOrderIterator(Node<T>* root = nullptr) : TreeIterator() {
            if (root != nullptr)
                visitPostOrder(root);
        }

        void visitPostOrder(Node<T>* node) {
            for (auto& child : *node)
                visitPostOrder(&child);
            this->nodeQueue.push(node);
        }

    };

    class InOrderIterator : public TreeIterator {
    public:
        explicit InOrderIterator(Node<T>* root = nullptr) {
            if (root != nullptr)
                visitInorder(root);
        }

        void visitInorder(Node<T>* node) {
            if (node->numChildren() >= 1)
                visitInorder(node->getChild(0));

            this->nodeQueue.push(node);

            if (node->numChildren() == 2)
                visitInorder(node->getChild(1));
        }
    };

    class DFSIterator : public TreeIterator {
    public:
        explicit DFSIterator(Node<T>* root = nullptr){
            if (root != nullptr)
                visitDFS(root);
        }

        void visitDFS(Node<T>* node) {
            for (auto& child : *node)
                visitDFS(&child);
            this->nodeQueue.push(node);
        }

    };

    TreeIterator begin() { return beginBFS(); }
    TreeIterator end() { return endBFS(); }

    TreeIterator beginBFS() { return BFSIterator(root); }
    TreeIterator endBFS() { return BFSIterator(); }

    TreeIterator beginDFS() { return DFSIterator(root); }
    TreeIterator endDFS() { return DFSIterator(); }

    TreeIterator beginPreOrder() {
        if (D == 2)
            return PreOrderIterator(root);
        return beginDFS();
    }
    TreeIterator endPreOrder() {
        if (D == 2)
            return PreOrderIterator();
        return endDFS();
    }

    TreeIterator beginPostOrder() {
        if (D == 2)
            return PostOrderIterator(root);
        return beginDFS();
    }
    TreeIterator endPostOrder() {
        if (D == 2)
            return PostOrderIterator();
        return endDFS();
    }

    TreeIterator beginInOrder() {
        if (D == 2)
            return InOrderIterator(root);
        return beginDFS();
    }
    TreeIterator endInOrder() {
        if (D == 2)
            return InOrderIterator();
        return endDFS();
    }

    TreeIterator beginHeap() {
        toHeap();
        return beginBFS();
    }
    TreeIterator endHeap() {
        return endBFS();
    }

    void clear() { delete root; root = nullptr; }

    /**
     * Turns the binary tree into a heap.
     */
    void toHeap();

};

template<typename T, unsigned int D>
void Tree<T, D>::toHeap() {
    if (D != 2)
        throw std::logic_error("Can only turn binary trees to heaps");

    // Sort the values of the tree
    std::vector<T> values;
    for (auto& node : *this)
        values.push_back(*node);
    std::sort(values.begin(), values.end());

    // Reconstruct the tree
    clear();
    root = new Node<T>(values[0], D);
    for (unsigned int i = 1; i < values.size(); i++)
        addSubNode(values[(i-1)/2], values[i]);
}

template<typename T, unsigned int D>
void Tree<T, D>::addSubNode(T parentValue, T childValue) {
    Node<T>* parent = nullptr;
    for (auto& node : *this) {
        if (*node == childValue)
            throw std::logic_error("The child node already exists in the tree");
        if (*node == parentValue)
            parent = &node;
    }
    if (parent == nullptr)
        throw std::logic_error("The parent node does not exist in the tree");
    if (parent->numChildren() >= D)
        throw std::logic_error("The parent has reached its maximum degree");
    parent->addChild(new Node<T>(childValue, D));
}

template<typename T, unsigned int D>
void Tree<T, D>::addRoot(T nodeValue) {
    if (root != nullptr)
        throw std::logic_error("The root of the tree has already been set");
    root = new Node<T>(nodeValue, D);
}

#endif // TREE_ITERATORS_TREE

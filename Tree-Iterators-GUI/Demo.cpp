// 326627635 | adi.peisach@gmail.com

#include "Screen.cpp"
#include <string>

using namespace std;

int main() {

    cout << "Binary tree:" << endl;
    Tree<double> tree; // Binary tree that contains doubles.

    tree.addRoot(1.1);
    tree.addSubNode(1.1, 1.2);
    tree.addSubNode(1.1, 1.3);
    tree.addSubNode(1.2, 1.4);
    tree.addSubNode(1.2, 1.5);
    tree.addSubNode(1.3, 1.6);
    tree.addSubNode(1.4, 1.7);

    for (auto& node : tree) {
        cout << *node << " ";
    } cout << endl;
    for (auto node = tree.beginBFS(); node != tree.endBFS(); ++node) {
        cout << **node << " ";
    } cout << endl;
    for (auto node = tree.beginDFS(); node != tree.endDFS(); ++node) {
        cout << **node << " ";
    } cout << endl;
    for (auto node = tree.beginPostOrder(); node != tree.endPostOrder(); ++node) {
        cout << **node << " ";
    } cout << endl;

    display(tree);

//    tree.display();
//    tree.toHeap();
//    tree.display();

    Tree<unsigned int, 3> three_ary_tree; // 3-ary tree.
    three_ary_tree.addRoot(1);
    three_ary_tree.addSubNode(1, 2);
    three_ary_tree.addSubNode(1, 3);
    three_ary_tree.addSubNode(1, 4);
    three_ary_tree.addSubNode(2, 5);
    three_ary_tree.addSubNode(2, 51);
    three_ary_tree.addSubNode(2, 52);
    three_ary_tree.addSubNode(3, 6);

    display(three_ary_tree);

//    three_ary_tree.display();

    Tree<string, 3> three_ary_tree2; // 3-ary tree.
    three_ary_tree2.addRoot("1");
    three_ary_tree2.addSubNode("1", "2");
    three_ary_tree2.addSubNode("1", "3");
    three_ary_tree2.addSubNode("1", "4");
    three_ary_tree2.addSubNode("2", "5");
    three_ary_tree2.addSubNode("2", "51");
    three_ary_tree2.addSubNode("2", "52");
    three_ary_tree2.addSubNode("3", "6");

//    three_ary_tree2.display();

    Tree<Complex, 2> complex_tree;
    complex_tree.addRoot(Complex(1.1, 2));
    complex_tree.addSubNode(Complex(1.1, 2), Complex(3, 4));
    complex_tree.addSubNode(Complex(1.1, 2), Complex(5, 6));
    complex_tree.addSubNode(Complex(3, 4), Complex(7, 8));
    complex_tree.addSubNode(Complex(3, 4), Complex(3, 1));
    complex_tree.addSubNode(Complex(3, 1), Complex(2, 10));

//    complex_tree.display();

    return 0;
}
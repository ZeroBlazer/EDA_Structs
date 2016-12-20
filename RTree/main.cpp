#include <iostream>
#include "RTree.h"

using namespace std;

typedef RTree<char[], int, 2, 3, 1> MyRTree;

int main() {
    cout << "Hello World!" << endl;

    MyRTree my_tree;
    my_tree.insert(MyRTree::Point(5, 45), "Denver");
    my_tree.insert(MyRTree::Point(90,  5), "Miami");
    my_tree.insert(MyRTree::Point(85, 15), "Atlanta");
    my_tree.insert(MyRTree::Point(52, 10), "Mobile");
    my_tree.insert(MyRTree::Point(82, 65), "Buffalo");
    my_tree.insert(MyRTree::Point(62, 77), "Toronto");
    my_tree.insert(MyRTree::Point(32, 42), "Chicago");
    my_tree.insert(MyRTree::Point(27, 35), "Omaha");

    return 0;
}
#include <iostream>
#include "RTree.h"

using namespace std;

typedef RTree<string, int, 2, 3, 2> MyRTree;

int main() {
    cout << "Hello World!" << endl;

    MyRTree my_tree;
    my_tree.insert(MyRTree::Point( 5, 45), string("Denver"));
    my_tree.insert(MyRTree::Point(27, 35), string("Omaha"));
    my_tree.insert(MyRTree::Point(82, 65), string("Buffalo"));
    // my_tree.insert(MyRTree::Point(62, 77), string("Toronto"));
    // my_tree.insert(MyRTree::Point(32, 42), string("Chicago"));
    // my_tree.insert(MyRTree::Point(52, 10), string("Mobile"));
    // my_tree.insert(MyRTree::Point(85, 15), string("Atlanta"));
    // my_tree.insert(MyRTree::Point(90,  5), string("Miami"));

    return 0;
}
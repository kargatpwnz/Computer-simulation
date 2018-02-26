#include <iostream>

#include "src/headers/Tree.h"
#include "src/headers/Graph.h"

int main()
{
    try {
        Graph graph(5, 7, 3);
        graph.generateGraph();
        graph.printTree();
    } catch (int err) {
        std::cout << err << std::endl;
    }

//    Tree tree(10, 3);
//    tree.printTree();

    return 0;
}

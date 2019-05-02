#include "Includes/AVLTree.h"
#include <iostream>

int main()
{
    AVLTree<int> tree;
    std::cout << tree.getTreeHeight() << std::endl;
    int arrat[] = {0,5,3,41,61,-6,-1,-71,-12,-51,1,51,-15};

    for(auto n: arrat)
    {
        tree.insert(n);
    }
    std::cout << tree.ToGraphviz();
    

    std::cin.get();
    return 0;
}
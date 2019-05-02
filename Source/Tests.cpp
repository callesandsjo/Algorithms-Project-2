#include "TestAVLTree.hpp"
#include <string>

int main()
{
    if(UnitTests::AVLTREE::AVLTreeUnitTests())
    {
        std::cout << "\nAll Unit Tests passed." << std::endl;
    }
    else
    {
        std::cout << "\nUnit tests failed on one or more tests." << std::endl;
        std::cout << "Please note that all tests must pass for your submission to be assessed." << std::endl;
    }
    std::cin.get();
}
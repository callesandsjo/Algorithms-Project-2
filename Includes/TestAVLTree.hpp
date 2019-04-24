#ifndef TEST_AVL_TREE_HPP
#define TEST_AVL_TREE_HPP

/*******************************************************************
*						Here be Dragons
********************************************************************/

#include "TestingBase.hpp"
#include <cstdint>
#include <iostream>

#if __has_include("AVLTree.h")
#include "AVLTree.h"
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <chrono>
#include <limits>
namespace UnitTests::AVLTREE
{

static constexpr bool AVLTree_IsDefaultConstructible = std::is_default_constructible<AVLTree<int>>::value;

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(insert)

static constexpr bool AVLTree_HasCorrectInsertFunction =    has_insert<AVLTree<int>, void, const int &>::value;
static constexpr bool AVLTree_HasIncorrectInsertFunction =  has_insert<AVLTree<int>, void, const int>::value || 
                                                            has_insert<AVLTree<int>, void, int &>::value || 
                                                            has_insert<AVLTree<int>, void, int>::value;
static constexpr bool AVLTree_HasInsertFunction = AVLTree_HasCorrectInsertFunction || AVLTree_HasIncorrectInsertFunction;

template <typename T = AVLTree<int>>
bool UnitTestBasicInsert()
{
    std::cout << "\n\tAVLTree::insert test begin." << std::endl;
    std::cout << "\tPlease note that this is a basic test that does not guarantee correct ordering of nodes." << std::endl;
    if constexpr (AVLTree_HasInsertFunction)
    {
        if constexpr (AVLTree_HasIncorrectInsertFunction)
        {
            std::cout << "\t\tAVLTree::insert does not have an optimal signature. Optimal signature would be void insert(const T&)." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        T tree;
        try
        {
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

            std::cout << "\t\tTesting insertion of 1'000 elements." << std::endl;
            for (int i = 0; i != 1'000; ++i)
                tree.insert(dist(engine));
            std::cout << "\t\t1'000 elements inserted." << std::endl;
        }
        catch (const std::exception &e)
        {
            std::cout << "\t\tException thrown during insertion of 1'000 elements: " << e.what() << std::endl;
            std::cout << "\tAVLTree::insert test end." << std::endl;
            return false;
        }
        catch (...)
        {
            std::cout << "\t\tException thrown during insertion of 1'000 elements." << std::endl;
            std::cout << "\tAVLTree::insert test end." << std::endl;
            return false;
        }

        std::cout << "\tAVLTree::insert test end." << std::endl;
        return true;
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::insert matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::insert test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(getMin)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getMin)

static constexpr bool AVLTree_HasCorrectgetMinFunction =   has_const_getMin<AVLTree<int>, const int &>::value;
static constexpr bool AVLTree_HasIncorrectgetMinFunction = has_const_getMin<AVLTree<int>, int>::value || 
                                                            has_const_getMin<AVLTree<int>, int &>::value || 
                                                            has_const_getMin<AVLTree<int>, const int>::value ||
                                                            has_getMin<AVLTree<int>, const int&>::value || 
                                                            has_getMin<AVLTree<int>, int>::value || 
                                                            has_getMin<AVLTree<int>, int &>::value || 
                                                            has_getMin<AVLTree<int>, const int>::value;
static constexpr bool AVLTree_HasgetMinFunction = AVLTree_HasCorrectgetMinFunction || AVLTree_HasIncorrectgetMinFunction;

template <typename T = AVLTree<int>>
bool UnitTestFindMin()
{
    std::cout << "\n\tAVLTree::getMin test begin." << std::endl;
    if constexpr (AVLTree_HasgetMinFunction)
    {
        if constexpr (AVLTree_HasIncorrectgetMinFunction)
        {
            std::cout << "\t\tAVLTree::getMin does not have an optimal signature. Optimal signature would be const T& getMin() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        if constexpr (AVLTree_HasInsertFunction)
        {
            T tree;
            std::vector<int> testData{0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15};

            std::cout << "\t\tThis test will insert a set into the AVLTree and expects getMin to return the minimum element inserted." << std::endl;
            std::cout << "\t\t\tInserting the set: {0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15} into the AVLTree." << std::endl;
            for(auto &&element : testData)
                tree.insert(element);
            std::cout << "\t\t\tInsertion done. Calling AVLTree::getMin." <<
                        "\n\t\t\t\tExpected result: -71"<<
                        "\n\t\t\t\tReturned result: " << tree.getMin() << std::endl;

            if(tree.getMin() != -71)
            {
                std::cout << "\t\t\tAVLTree::getMin did not return expected element. Returned: " << tree.getMin() << std::endl;
                std::cout << "\t\tAVLTree::getMin not working as expected." << std::endl;
                std::cout << "\tAVLTree::getMin test end." << std::endl;
                return false;
            }
            
            std::cout << "\t\t\tAVLTree::getMin returned expected element." << std::endl;
            std::cout << "\t\tAVLTree::getMin working as expected." << std::endl;
            std::cout << "\tAVLTree::getMin test end." << std::endl;
            return true;
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::getMin." << std::endl;
            std::cout << "\tAVLTree::getMin test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::getMin matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::getMin test end." << std::endl;
        return false;
    }
}


GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(getMax)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getMax)

static constexpr bool AVLTree_HasCorrectgetMaxFunction =   has_const_getMax<AVLTree<int>, const int &>::value;
static constexpr bool AVLTree_HasIncorrectgetMaxFunction = has_const_getMax<AVLTree<int>, int>::value || 
                                                            has_const_getMax<AVLTree<int>, int &>::value || 
                                                            has_const_getMax<AVLTree<int>, const int>::value ||
                                                            has_getMax<AVLTree<int>, const int&>::value || 
                                                            has_getMax<AVLTree<int>, int>::value || 
                                                            has_getMax<AVLTree<int>, int &>::value || 
                                                            has_getMax<AVLTree<int>, const int>::value;
static constexpr bool AVLTree_HasgetMaxFunction = AVLTree_HasCorrectgetMaxFunction || AVLTree_HasIncorrectgetMaxFunction;

template <typename T = AVLTree<int>>
bool UnitTestFindMax()
{
    std::cout << "\n\tAVLTree::getMax test begin." << std::endl;
    if constexpr (AVLTree_HasgetMaxFunction)
    {
        if constexpr (AVLTree_HasIncorrectgetMaxFunction)
        {
            std::cout << "\t\tAVLTree::getMax does not have an optimal signature. Optimal signature would be const T& getMax() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        if constexpr(AVLTree_HasInsertFunction)
        {
            T tree;
            std::vector<int> testData{0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15};

            std::cout << "\t\tThis test will insert a set into the AVLTree and expects getMax to return the maximum element inserted." << std::endl;
            std::cout << "\t\t\tInserting the set: {0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15} into the AVLTree." << std::endl;
            for(auto &&element : testData)
                tree.insert(element);
            std::cout << "\t\t\tInsertion done. Calling AVLTree::getMax." <<
                        "\n\t\t\t\tExpected result: 61"<<
                        "\n\t\t\t\tReturned result: " << tree.getMax() << std::endl;

            if(tree.getMax() != 61)
            {
                std::cout << "\t\t\tAVLTree::getMax did not return expected element. Returned: " << tree.getMax() << std::endl;
                std::cout << "\t\tAVLTree::getMax not working as expected." << std::endl;
                std::cout << "\tAVLTree::getMax test end." << std::endl;
                return false;
            }
            
            std::cout << "\t\t\tAVLTree::getMax returned expected element." << std::endl;
            std::cout << "\t\tAVLTree::getMax working as expected." << std::endl;
            std::cout << "\tAVLTree::getMax test end." << std::endl;
            return true;
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::getMax." << std::endl;
            std::cout << "\tAVLTree::getMax test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::getMax matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::getMax test end." << std::endl;
        return false;
    }
}


GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(find)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(find)

static constexpr bool AVLTree_HasCorrectfindFunction =   has_const_find<AVLTree<int>, bool, const int &>::value;
static constexpr bool AVLTree_HasIncorrectfindFunction = has_const_find<AVLTree<int>, bool, int>::value || 
                                                            has_const_find<AVLTree<int>, bool, int &>::value || 
                                                            has_const_find<AVLTree<int>, bool, const int>::value ||
                                                            has_find<AVLTree<int>, bool, const int&>::value || 
                                                            has_find<AVLTree<int>, bool, int>::value || 
                                                            has_find<AVLTree<int>, bool, int &>::value || 
                                                            has_find<AVLTree<int>, bool, const int>::value;
static constexpr bool AVLTree_HasfindFunction = AVLTree_HasCorrectfindFunction || AVLTree_HasIncorrectfindFunction;

template <typename T = AVLTree<int>>
bool UnitTestFind()
{
    std::cout << "\n\tAVLTree::find test begin." << std::endl;
    if constexpr (AVLTree_HasfindFunction)
    {
        if constexpr (AVLTree_HasIncorrectfindFunction)
        {
            std::cout << "\t\tAVLTree::find does not have an optimal signature. Optimal signature would be bool getMax(const T&) const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        if constexpr (AVLTree_HasInsertFunction)
        {
            T tree;
            std::vector<int> testData{0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15};

            std::cout << "\t\tThis test will insert a set into the AVLTree and expects find to return if a specified element is inserted or not." << std::endl;
            std::cout << "\t\t\tInserting the set: {0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15} into the AVLTree." << std::endl;
            for(auto &&element : testData)
                tree.insert(element);
            std::cout << "\t\t\tInsertion done. Calling AVLTree::find, searching for element 5." <<
                        "\n\t\t\t\tExpected result: true"<<
                        "\n\t\t\t\tReturned result: " << std::boolalpha << tree.find(5) << std::endl;

            if(!tree.find(5))
            {
                std::cout << "\t\t\tAVLTree::find did not return expected element. Returned: " << std::boolalpha << false << std::endl;
                std::cout << "\t\tAVLTree::find not working as expected." << std::endl;
                std::cout << "\tAVLTree::find test end." << std::endl;
                return false;
            }
            
            std::cout << "\t\t\tAVLTree::find(5) returned expected element." << std::endl;

            std::cout << "\t\t\tInsertion done. Calling AVLTree::find, searching for element -72." <<
                        "\n\t\t\t\tExpected result: false"<<
                        "\n\t\t\t\tReturned result: " << std::boolalpha << tree.find(-72) << std::endl;

            if(tree.find(-72))
            {
                std::cout << "\t\t\tAVLTree::find did not return expected element. Returned: " << std::boolalpha << true << std::endl;
                std::cout << "\t\tAVLTree::find not working as expected." << std::endl;
                std::cout << "\tAVLTree::find test end." << std::endl;
                return false;
            }
            
            std::cout << "\t\t\tAVLTree::find(-72) returned expected element." << std::endl;
            std::cout << "\t\tAVLTree::find working as expected." << std::endl;
            std::cout << "\tAVLTree::find test end." << std::endl;
            return true;
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::find." << std::endl;
            std::cout << "\tAVLTree::find test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::find matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::find test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(getTreeHeight)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(getTreeHeight)

static constexpr bool AVLTree_HasCorrectgetTreeHeightFunction =   has_const_getTreeHeight<AVLTree<int>, size_t>::value;
static constexpr bool AVLTree_HasIncorrectgetTreeHeightFunction = has_getTreeHeight<AVLTree<int>, size_t>::value;
static constexpr bool AVLTree_HasgetTreeHeightFunction = AVLTree_HasCorrectgetTreeHeightFunction || AVLTree_HasIncorrectgetTreeHeightFunction;

template <typename T = AVLTree<int>>
bool UnitTestGetTreeHeight()
{
    std::cout << "\n\tAVLTree::getTreeHeight test begin." << std::endl;
    if constexpr(AVLTree_HasgetTreeHeightFunction)
    {
        if constexpr(AVLTree_HasIncorrectgetTreeHeightFunction)
        {            
            std::cout << "\t\tAVLTree::getTreeHeight does not have an optimal signature. Optimal signature would be size_t getTreeHeight() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        
        T tree;

        std::cout << "\t\tThis test will try to get the height of an empty tree.\n\t\t\tExpected value: -1" << std::endl;
        size_t height = tree.getTreeHeight();
        std::cout << "\t\t\tReturned value: " << (height == std::numeric_limits<size_t>::max() ? std::string("-1") : std::to_string(height)) << std::endl;
        if(height != std::numeric_limits<size_t>::max())
        {
            std::cout << "\t\t\tAVLTree::getTreeHeight did not return expected value." << std::endl;
            std::cout << "\t\tAVLTree::getTreeHeight not working as expected." << std::endl;
            std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
            return false;
        }
        std::cout << "\t\tAVLTree::getTreeHeight returned expected value on empty tree." << std::endl;
        if constexpr (AVLTree_HasInsertFunction)
        {
            std::cout << "\t\tThis test will insert the set {3,2,1,4,5,6,7} before calling getTreeHeight() on the tree." << std::endl;
            std::vector range{3, 2, 1, 4, 5, 6, 7};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple rotations. Calling getTreeHeight." << std::endl;
            std::cout << "\t\t\t\tExpected value: 2" << std::endl;
            height = tree.getTreeHeight();
            std::cout << "\t\t\t\tReturned value: " << height << std::endl;
            if(height != 2)
            {
                std::cout << "\t\t\tAVLTree::getTreeHeight did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::getTreeHeight not working as expected." << std::endl;
                std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::getTreeHeight() returned expected value on the set. Continuing with insertion of the second set {16, 15, 14, 13, 12, 11, 10, 8, 9}." << std::endl;
            range.clear();
            range = {16, 15, 14, 13, 12, 11, 10, 8, 9};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple double rotations. Calling getTreeHeight." << std::endl;
            std::cout << "\t\t\t\tExpected value: 4" << std::endl;
            height = tree.getTreeHeight();
            std::cout << "\t\t\t\tReturned value: " << height << std::endl;
            if(height != 4)
            {
                std::cout << "\t\t\tAVLTree::getTreeHeight did not return expected value, see page 167-171 for example." << std::endl;
                std::cout << "\t\tAVLTree::getTreeHeight not working as expected." << std::endl;
                std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::getTreeHeight returned expected value on the set." << std::endl;
            std::cout << "\t\tAVLTree::getTreeHeight working as expected." << std::endl;
            std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
            return true;
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct further tests on AVLTree::getTreeHeight." << std::endl;
            std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::getTreeHeight matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::getTreeHeight test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(preOrderWalk)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(preOrderWalk)

static constexpr bool AVLTree_HasCorrectpreOrderWalkFunction =   has_const_preOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HasIncorrectpreOrderWalkFunction = has_preOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HaspreOrderWalkFunction = AVLTree_HasCorrectpreOrderWalkFunction || AVLTree_HasIncorrectpreOrderWalkFunction;


template <typename T = AVLTree<int>>
bool UnitTestPreOrderWalk()
{
    std::cout << "\n\tAVLTree::preOrderWalk test begin." << std::endl;
    if constexpr(AVLTree_HaspreOrderWalkFunction)
    {
        if constexpr(AVLTree_HasIncorrectpreOrderWalkFunction)
        {            
            std::cout << "\t\tAVLTree::preOrderWalk does not have an optimal signature. Optimal signature would be size_t preOrderWalk() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        
        T tree;

        std::cout << "\t\tThis test will try to get the preOrderWalk of an empty tree." << std::endl;
        std::vector<int> walkResult = tree.preOrderWalk();
        
        if(walkResult.size())
        {
            std::cout << "\t\t\tAVLTree::preOrderWalk did not return as expected. size() indicates that elements are placed in the return vector when non should be." << std::endl;
            std::cout << "\t\tAVLTree::preOrderWalk not working as expected." << std::endl;
            std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
            return false;
        }
        std::cout << "\t\tAVLTree::preOrderWalk returned expected value on empty tree." << std::endl;
        if constexpr (AVLTree_HasInsertFunction)
        {
            std::cout << "\t\tThis test will insert the set {3,2,1,4,5,6,7} before calling preOrderWalk() on the tree." << std::endl;
            std::vector range{3, 2, 1, 4, 5, 6, 7};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple rotations. Calling preOrderWalk." << std::endl;
            range = {4, 2, 1, 3, 6, 5, 7};
            std::cout << "\t\t\t\tExpected value: {4, 2, 1, 3, 6, 5, 7}" << std::endl;
            walkResult = tree.preOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::preOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::preOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(range != walkResult)
            {
                std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::preOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::preOrderWalk() returned expected value on the set. Continuing with insertion of the second set {16, 15, 14, 13, 12, 11, 10, 8, 9}." << std::endl;
            range.clear();
            range = {16, 15, 14, 13, 12, 11, 10, 8, 9};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple double rotations. Calling preOrderWalk." << std::endl;
            std::cout << "\t\t\t\tExpected value: {7, 4, 2, 1, 3, 6, 5, 13, 11, 9, 8, 10, 12, 15, 14, 16}" << std::endl;
            walkResult = tree.preOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::preOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::preOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(walkResult != std::vector<int>{7, 4, 2, 1, 3, 6, 5, 13, 11, 9, 8, 10, 12, 15, 14, 16})
            {
                std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::preOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::preOrderWalk returned expected value on the set." << std::endl;
            std::cout << "\t\tAVLTree::preOrderWalk working as expected." << std::endl;
            std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
            return true;
        }
        
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::preOrderWalk." << std::endl;
            std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::preOrderWalk matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::preOrderWalk test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(inOrderWalk)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(inOrderWalk)

static constexpr bool AVLTree_HasCorrectinOrderWalkFunction =   has_const_inOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HasIncorrectinOrderWalkFunction = has_inOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HasinOrderWalkFunction = AVLTree_HasCorrectinOrderWalkFunction || AVLTree_HasIncorrectinOrderWalkFunction;

template <typename T = AVLTree<int>>
bool UnitTestInOrderWalk()
{
std::cout << "\n\tAVLTree::inOrderWalk test begin." << std::endl;
    if constexpr(AVLTree_HasinOrderWalkFunction)
    {
        if constexpr(AVLTree_HasIncorrectinOrderWalkFunction)
        {            
            std::cout << "\t\tAVLTree::inOrderWalk does not have an optimal signature. Optimal signature would be size_t inOrderWalk() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        
        T tree;

        std::cout << "\t\tThis test will try to get the inOrderWalk of an empty tree." << std::endl;
        std::vector<int> walkResult = tree.inOrderWalk();
        
        if(walkResult.size())
        {
            std::cout << "\t\t\tAVLTree::inOrderWalk did not return as expected. size() indicates that elements are placed in the return vector when non should be." << std::endl;
            std::cout << "\t\tAVLTree::inOrderWalk not working as expected." << std::endl;
            std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
            return false;
        }
        std::cout << "\t\tAVLTree::inOrderWalk returned expected value on empty tree." << std::endl;
        if constexpr (AVLTree_HasInsertFunction)
        {
            std::cout << "\t\tThis test will insert the set {3,2,1,4,5,6,7} before calling inOrderWalk() on the tree." << std::endl;
            std::vector range{3, 2, 1, 4, 5, 6, 7};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple rotations. Calling inOrderWalk." << std::endl;
            std::cout << "\t\t\t\tExpected value: {1, 2, 3, 4, 5, 6, 7}" << std::endl;
            walkResult = tree.inOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::inOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::inOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(!std::is_sorted(walkResult.begin(), walkResult.end()))
            {
                std::cout << "\t\t\tAVLTree::inOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::inOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::inOrderWalk() returned expected value on the set. Continuing with insertion of the second set {16, 15, 14, 13, 12, 11, 10, 8, 9}." << std::endl;
            range.clear();
            range = {16, 15, 14, 13, 12, 11, 10, 8, 9};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple double rotations. Calling inOrderWalk." << std::endl;
            std::cout << "\t\t\t\tExpected value: {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}" << std::endl;
            walkResult = tree.inOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::inOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::inOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(!std::is_sorted(walkResult.begin(), walkResult.end()))
            {
                std::cout << "\t\t\tAVLTree::inOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::inOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::inOrderWalk returned expected value on the set." << std::endl;
            std::cout << "\t\tAVLTree::inOrderWalk working as expected." << std::endl;
            std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
            return true;
        }        
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::inOrderWalk." << std::endl;
            std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::inOrderWalk matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::inOrderWalk test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(postOrderWalk)
GENERATE_SAME_NAME_HAS_CONST_MEMBER_FUNCTION(postOrderWalk)

static constexpr bool AVLTree_HasCorrectpostOrderWalkFunction =   has_const_postOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HasIncorrectpostOrderWalkFunction = has_postOrderWalk<AVLTree<int>, std::vector<int>>::value;
static constexpr bool AVLTree_HaspostOrderWalkFunction = AVLTree_HasCorrectpostOrderWalkFunction || AVLTree_HasIncorrectpostOrderWalkFunction;
template <typename T = AVLTree<int>>
bool UnitTestPostOrderWalk()
{
    std::cout << "\n\tAVLTree::postOrderWalk test begin." << std::endl;
    if constexpr(AVLTree_HaspostOrderWalkFunction)
    {
        if constexpr(AVLTree_HasIncorrectpostOrderWalkFunction)
        {            
            std::cout << "\t\tAVLTree::postOrderWalk does not have an optimal signature. Optimal signature would be size_t postOrderWalk() const." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;
        }
        
        T tree;

        std::cout << "\t\tThis test will try to get the postOrderWalk of an empty tree." << std::endl;
        std::vector<int> walkResult = tree.postOrderWalk();
        
        if(walkResult.size())
        {
            std::cout << "\t\t\tAVLTree::postOrderWalk did not return as expected. size() indicates that elements are placed in the return vector when non should be." << std::endl;
            std::cout << "\t\tAVLTree::postOrderWalk not working as expected." << std::endl;
            std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
            return false;
        }
        std::cout << "\t\tAVLTree::postOrderWalk returned expected value on empty tree." << std::endl;
        if constexpr (AVLTree_HasInsertFunction)
        {
            std::cout << "\t\tThis test will insert the set {3,2,1,4,5,6,7} before calling postOrderWalk() on the tree." << std::endl;
            std::vector range{3, 2, 1, 4, 5, 6, 7};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple rotations. Calling postOrderWalk." << std::endl;
            range = {1, 3, 2, 5, 7, 6, 4};
            std::cout << "\t\t\t\tExpected value: {1, 3, 2, 5, 7, 6, 4}" << std::endl;
            walkResult = tree.postOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::postOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::postOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(range != walkResult)
            {
                std::cout << "\t\t\tAVLTree::postOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::postOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::postOrderWalk() returned expected value on the set. Continuing with insertion of the second set {16, 15, 14, 13, 12, 11, 10, 8, 9}." << std::endl;
            range.clear();
            range = {16, 15, 14, 13, 12, 11, 10, 8, 9};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple double rotations. Calling postOrderWalk." << std::endl;
            std::cout << "\t\t\t\tExpected value: {1, 3, 2, 5, 6, 4, 8, 10, 9, 12, 11, 14, 16, 15, 13, 7}" << std::endl;
            walkResult = tree.postOrderWalk();
            if(!walkResult.size())
            {
                std::cout << "\t\t\tAVLTree::postOrderWalk did not return any elements." << std::endl;
                std::cout << "\t\tAVLTree::postOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\t\tReturned value: {";
            for(size_t i = 0; i != walkResult.size() - 1; ++i)
            {
                std::cout << walkResult[i] << ", ";
            }
            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
            if(walkResult != std::vector<int>{1, 3, 2, 5, 6, 4, 8, 10, 9, 12, 11, 14, 16, 15, 13, 7})
            {
                std::cout << "\t\t\tAVLTree::postOrderWalk did not return expected value, see page 165-167 for example." << std::endl;
                std::cout << "\t\tAVLTree::postOrderWalk not working as expected." << std::endl;
                std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
                return false;
            }
            std::cout << "\t\t\tAVLTree::postOrderWalk returned expected value on the set." << std::endl;
            std::cout << "\t\tAVLTree::postOrderWalk working as expected." << std::endl;
            std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
            return true;
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::postOrderWalk." << std::endl;
            std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
            return false;
        }
    }
    else
    {
        std::cout << "\t\tNo function AVLTree::postOrderWalk matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::postOrderWalk test end." << std::endl;
        return false;
    }
}

GENERATE_SAME_NAME_HAS_MEMBER_FUNCTION(remove)

static constexpr bool AVLTree_HasCorrectremoveFunction = has_remove<AVLTree<int>, void, const int&>::value;
static constexpr bool AVLTree_HasIncorrectremoveFunction =  has_remove<AVLTree<int>, void, const int>::value ||
                                                            has_remove<AVLTree<int>, void, int&>::value ||
                                                            has_remove<AVLTree<int>, void, int>::value;
static constexpr bool AVLTree_HasremoveFunction = AVLTree_HasCorrectremoveFunction || AVLTree_HasIncorrectremoveFunction;

template <typename T = AVLTree<int>>
bool UnitTestRemove()
{
    std::cout << "\n\tAVLTree::remove test begin." << std::endl;
    if constexpr(AVLTree_HasremoveFunction)
    {
        if constexpr(AVLTree_HasIncorrectremoveFunction)
        {
            std::cout << "\t\tAVLTree::remove does not have an optimal signature. Optimal signature would be void remove(const int&)." << std::endl;
            std::cout << "\t\t\tNote that this does not need to be changed." << std::endl;            
        }

        if constexpr (AVLTree_HasInsertFunction)
        {
            T tree;
            std::cout << "\t\tThis test will insert the set {3,2,1,4,5,6,7, 16, 15, 14, 13, 12, 11, 10, 8, 9} before removing various nodes on the tree." << std::endl;
            std::vector range{3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
            for(auto &&element : range)
            {
                tree.insert(element);
            }
            std::cout << "\t\t\tSet inserted into the AVLTree. This set should have resulted in multiple rotations and double rotations." << std::endl;
            std::cout << "\t\t\tCalling AVLTree::remove(12)" << std::endl;
            tree.remove(12);
            std::vector<int> walkResult;
            if constexpr (AVLTree_HaspreOrderWalkFunction && AVLTree_HaspostOrderWalkFunction)
            {
                std::cout << "\t\t\t\tRemove finished. Testing correctness with call to AVLTree::postOrderWalk and AVLTree::preOrderWalk" << std::endl;
                std::cout << "\t\t\t\tExpected value (preOrderWalk): {7, 4, 2, 1, 3, 6, 5, 13, 9, 8, 11, 10, 15, 14, 16}" << std::endl;
                walkResult = tree.preOrderWalk();
                std::cout << "\t\t\t\tReturned value (preOrderWalk): {";
                for(size_t i = 0; i != walkResult.size() - 1; ++i)
                {
                    std::cout << walkResult[i] << ", ";
                }
                std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
                if(walkResult != std::vector<int>{7, 4, 2, 1, 3, 6, 5, 13, 9, 8, 11, 10, 15, 14, 16})
                {
                    std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value after call to AVLTree::remove." << std::endl;
                    std::cout << "\t\tAVLTree::remove not working as expected." << std::endl;
                    std::cout << "\tAVLTree::remove test end." << std::endl;
                    return false;
                }
                walkResult = tree.postOrderWalk();
                std::cout << "\t\t\t\tExpected value (postOrderWalk): {1, 3, 2, 5, 6, 4, 8, 10, 11, 9, 14, 16, 15, 13, 7}" << std::endl;
                std::cout << "\t\t\t\tReturned value (postOrderWalk): {";
                for(size_t i = 0; i != walkResult.size() - 1; ++i)
                {
                    std::cout << walkResult[i] << ", ";
                }
                std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
                if(walkResult != std::vector<int>{1, 3, 2, 5, 6, 4, 8, 10, 11, 9, 14, 16, 15, 13, 7})
                {
                    std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value after call to AVLTree::remove." << std::endl;
                    std::cout << "\t\tAVLTree::remove not working as expected." << std::endl;
                    std::cout << "\tAVLTree::remove test end." << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "\t\t\t\tRemove finished. Unable to test correctness." << std::endl;
                std::cout << "\t\t\t\tAVLTree::preOrderWalk and AVLTree::postOrderWalk needed to verify AVLTree::remove." << std::endl;
            }
            std::cout << "\t\t\tCalling AVLTree::remove(8)" << std::endl;
            tree.remove(8);
            if constexpr(AVLTree_HaspostOrderWalkFunction && AVLTree_HaspreOrderWalkFunction)
            {
                std::cout << "\t\t\t\tRemove finished. Testing correctness with call to AVLTree::postOrderWalk and AVLTree::preOrderWalk" << std::endl;
                std::cout << "\t\t\t\tExpected value (preOrderWalk): {7, 4, 2, 1, 3, 6, 5, 13, 10, 9, 11, 15, 14, 16}" << std::endl;
                walkResult = tree.preOrderWalk();
                std::cout << "\t\t\t\tReturned value (preOrderWalk): {";
                for(size_t i = 0; i != walkResult.size() - 1; ++i)
                {
                    std::cout << walkResult[i] << ", ";
                }
                std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
                if(walkResult != std::vector<int>{7, 4, 2, 1, 3, 6, 5, 13, 10, 9, 11, 15, 14, 16})
                {
                    std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value after call to AVLTree::remove." << std::endl;
                    std::cout << "\t\tAVLTree::remove not working as expected." << std::endl;
                    std::cout << "\tAVLTree::remove test end." << std::endl;
                    return false;
                }
                walkResult = tree.postOrderWalk();
                std::cout << "\t\t\t\tExpected value (postOrderWalk): {1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7}" << std::endl;
                std::cout << "\t\t\t\tReturned value (postOrderWalk): {";
                for(size_t i = 0; i != walkResult.size() - 1; ++i)
                {
                    std::cout << walkResult[i] << ", ";
                }
                std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
                if(walkResult != std::vector<int>{1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7})
                {
                    std::cout << "\t\t\tAVLTree::preOrderWalk did not return expected value after call to AVLTree::remove." << std::endl;
                    std::cout << "\t\tAVLTree::remove not working as expected." << std::endl;
                    std::cout << "\tAVLTree::remove test end." << std::endl;
                    return false;
                }
            }
            else
            {
                std::cout << "\t\t\t\tRemove finished. Unable to test correctness." << std::endl;
                std::cout << "\t\t\t\tAVLTree::preOrderWalk and AVLTree::postOrderWalk needed to verify AVLTree::remove." << std::endl;
            }
            std::cout << "\t\t\tCalling remove on remaining elements in the order {1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7}" << std::endl;
            std::cout << "\t\t\t\tRemoving element: ";
            for(auto &&element : {1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7})
            {
                std::cout << element << " ";
                tree.remove(element);
            }
            std::cout << std::endl;
            if constexpr(AVLTree_HasgetTreeHeightFunction)
            {
                std::cout << "\t\t\tControlling that all elements have been properly removed." << std::endl;
                if(tree.getTreeHeight() != std::numeric_limits<size_t>::max())
                {
                    std::cout << "\t\t\tAVLTree::getTreeHeight did not return -1 on tree that is expected to be empty. " << std::endl;
                    if constexpr (AVLTree_HasinOrderWalkFunction)
                    {
                        walkResult = tree.inOrderWalk();
                        if(walkResult.size())
                        {
                            std::cout << "Elements remaining: {";
                            for(size_t i = 0; i != walkResult.size() - 1; ++i)
                            {
                                std::cout << walkResult[i] << ", ";
                            }
                            std::cout << walkResult[walkResult.size() - 1] << "}" << std::endl;
                        }
                        else
                        {
                            std::cout << "\t\t\tNo elements returned from call to AVLTree::inOrderWalk. This error should not be seen, since it indicates that the getTreeHeight test passed wrongly." << std::endl;
                            std::cout << "\t\t\tPlease contact Andreas, since this is a corner case unexpected to be seen." << std::endl;
                        }
                    }
                    else
                    {
                        std::cout << "\t\t\tAVLTree::inOrderWalk needed to print remaning elements." << std::endl;
                    }
                    std::cout << "\t\tAVLTree::remove not working as expected." << std::endl;
                    std::cout << "\tAVLTree::remove test end." << std::endl;
                    return false;
                }
                std::cout << "\t\tAVLTree::remove working as expected." << std::endl;
                std::cout << "\tAVLTree::remove test end." << std::endl;
                return true;
            }
            else
            {
                std::cout << "\t\t\t\tRemove finished. Unable to test correctness." << std::endl;
                std::cout << "\t\t\t\tAVLTree::getTreeHeight needed to verify AVLTree::remove." << std::endl;
                return false;
            }
        }
        else
        {
            std::cout << "\t\tAVLTree::insert needed to conduct tests on AVLTree::remove." << std::endl;
            std::cout << "\tAVLTree::remove test end." << std::endl;
            return false;
        }
    }    
    else
    {
        std::cout << "\t\tNo function AVLTree::remove matches the description given in the assignment." << std::endl;
        std::cout << "\tAVLTree::remove test end." << std::endl;
        return false;
    }
}

template <typename T = AVLTree<int>>
bool UnitTestThrow()
{
    std::cout << "\n\tTesting exceptions on the AVLTree." << std::endl;
    if constexpr (AVLTree_HasgetMaxFunction && AVLTree_HasgetMinFunction)
    {
        T tree;
        std::cout << "\t\tCalling AVLTree::getMin on an empty AVLTree." << std::endl;
        try
        {
            tree.getMin();
            std::cout << "\t\tAVLTree::getMin not throwing error as expected." << std::endl;
            std::cout << "\tException tests end." << std::endl;
            return false;
        }
        catch(std::exception &e)
        {
            std::cout << "\t\tCaught error: " << e.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "\t\tError caught." << std::endl;
        }
        std::cout << "\t\tCalling AVLTree::getMax on an empty AVLTree." << std::endl;
        try
        {
            tree.getMax();
            std::cout << "\t\tAVLTree::getMax not throwing error as expected." << std::endl;
            std::cout << "\tException tests end." << std::endl;            
            return false;
        }
        catch(std::exception &e)
        {
            std::cout << "\t\tCaught error: " << e.what() << std::endl;
        }
        catch(...)
        {
            std::cout << "\t\tError caught." << std::endl;
        }
        std::cout << "\t\tExceptions thrown as expected on the implemented AVLTree." << std::endl;
        std::cout << "\tException tests end." << std::endl;
        return true;
    }
    else
    {
        std::cout << "\t\tAVLTree::getMax and/or AVLTree::getMin does not exist." << std::endl;
        std::cout << "\tException tests end." << std::endl;
        return false;
    }
}

template <typename T = AVLTree<int>>
bool UnitTestStressTest()
{
    std::cout << "\tStarting Stress Test" << std::endl;
    if constexpr (AVLTree_HasInsertFunction && AVLTree_HasremoveFunction && AVLTree_HasgetMaxFunction 
        && AVLTree_HasgetMinFunction && AVLTree_HasgetTreeHeightFunction)
    {
        std::cout << "\t\tThe stress test will first add 1'000 randomized elements." << std::endl;
        std::mt19937 engine;
        std::uniform_int_distribution dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        std::vector<int> randomNumbs;
        std::cout << "\t\t\tRandomizing elements." << std::endl;
        while(randomNumbs.size() != 1'000)
        {
            int randNumb = dist(engine);
            if(std::find(randomNumbs.begin(), randomNumbs.end(), randNumb) != randomNumbs.end())
            {
                continue;
            }
            randomNumbs.push_back(randNumb);
        }
        std::cout << "\t\t\t1'000 elements created. Inserting into the tree." << std::endl;
        T tree;
        for(auto &&element : randomNumbs)
            tree.insert(element);
        std::cout << "\t\t\tInsertion done. Checking height of tree." << std::endl;
        if(tree.getTreeHeight() >= static_cast<size_t>(ceil(2*log2(1'000) + 2)) )
        {
            std::cout << "\t\t\t\tAVLTree::getTreeHeight indicates a tree that is higher than it should be." << std::endl;
            std::cout << "\t\t\t\tExpected: <" << static_cast<unsigned int>(ceil(2*log2(1'000) + 2)) << std::endl;
            std::cout << "\t\t\t\tRecieved:  " << tree.getTreeHeight() << std::endl;
        }
        else
        {
            std::cout << "\t\t\t\tAVLTree::getTreeHeight indicates a tree of correct height." << std::endl;
        }

        std::cout << "\t\t\tSecondly, elements will be added and removed in such a way that 250 elements are removed before 100 new are inserted." << std::endl;
        std::cout << "\t\t\tThis will be done until the tree is empty." << std::endl;
        auto it = randomNumbs.begin();
        unsigned short counter = 0;
        while(tree.getTreeHeight() != std::numeric_limits<size_t>::max())
        {
            tree.remove(*it);
            ++counter;
            ++it;
            if(counter == 250)
            {
                std::cout << "\t\t\t\t250 elements removed. Inserting 100 new." << std::endl;
                randomNumbs.erase(randomNumbs.begin(), it);
                for(unsigned short i = 0; i != 100; ++i)
                {
                    int randomNumb = dist(engine);
                    while(std::find(randomNumbs.begin(), randomNumbs.end(), randomNumb) != randomNumbs.end())
                        randomNumb = dist(engine);
                    tree.insert(randomNumb);
                    randomNumbs.push_back(randomNumb);
                }
                it = randomNumbs.begin();
                counter = 0;
            }
        }
        std::cout << "\t\t\tTree empty." << std::endl;
        std::cout << "\t\tStress test passed." << std::endl;
        std::cout << "\tStress test end." << std::endl;

        return true;
    }
    else
    {
        std::cout << "\t\tStress Test cannot be conducted. One or more functions are not implemented." << std::endl;
        std::cout << "\tStress test end." << std::endl;
        return false;
    }
}

template <typename T = AVLTree<int>>
bool AVLTreeUnitTests()
{
    if (AVLTree_IsDefaultConstructible)
    {
        std::cout << "AVLTree Unit Tests begin." << std::endl;
        try
        {
            std::cout << "\n\tTesting default constructor for AVLTree." << std::endl;
            T tree;
			tree = T();
        }
        catch (...)
        {
            std::cout << "\t\tDefault constructor threw an error. Further testing cannot be conducted." << std::endl;
        }
        std::cout << "\tDefault constructor for AVLTree working as expected." << std::endl;

        if (!UnitTestBasicInsert())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }

        if(!UnitTestFindMin())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }

        if(!UnitTestFindMax())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }

        if(!UnitTestFind())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestGetTreeHeight())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestPreOrderWalk())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestInOrderWalk())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestPostOrderWalk())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestRemove())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestThrow())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        if(!UnitTestStressTest())
        {
            std::cout << "AVLTree Unit Tests indicated error, further testing cannot be conducted." << std::endl;
            return false;
        }
        
        std::cout << "\nAVLTree Unit Tests end." << std::endl;
        return true;
    }
    else
    {
        std::cout << "AVLTree Unit Tests cannot be conducted, no defaul constructor available." << std::endl;
        return false;
    }
}
} // namespace UnitTests::AVLTREE
#else
namespace UnitTests::AVLTREE
{
bool AVLTreeUnitTests()
{
    std::cout << "File AVLTree.h non-existent." << std::endl;
    return false;
}
} // namespace UnitTests::AVLTREE
#endif

#endif
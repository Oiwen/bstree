#include <iostream>
#include <memory>
#include <random>
#include <algorithm>

#include "bst.h"

void testNonMoveableInsert();
void testMoveableInsert();
void testFindMin();
void testFindMax();
void testRemove();

int main()
{
    // Say Hello :)
    std::cout << "Binary Search Tree" << std::endl;

    // Testing ctros and = operators

    // int x = 1, y = 7, z = 4, k = 6;
    BST<int> btree1;
    btree1.insert(1);
    btree1.insert(7);
    btree1.insert(4);
    btree1.insert(5);

    std::cout << "Printing btree1: ";
    btree1.print();

    BST<int> btree2 = std::move(btree1);
    std::cout << "Printing btree2: ";
    btree2.print();
    
    // testNonMoveableInsert();
    // testMoveableInsert();
    // testFindMin();
    // testFindMax();
    // testRemove();

    return 0;
}

void testNonMoveableInsert()
{
    std::cout << "*****"
              << "Testing non moveable insert" << std::endl;
    // Create RNG
    std::mt19937 rng;
    // Init seed
    rng.seed(std::random_device()());
    // Set lower and upper bounds
    int lowerBound = 0, upperBound = 10;
    std::uniform_int_distribution<int> dist(lowerBound, upperBound);

    BST<int> bstree;
    // Set nodes count
    size_t nodeCount = 25;
    // Create some vector, for further tests
    std::vector<int> nodesVals;
    nodesVals.reserve(nodeCount);
    // Start to fill it
    for (size_t i = 0; i < nodeCount; ++i)
    {
        int value = dist(rng);
        bstree.insert(value);
        nodesVals.push_back(value);
    }

    // if (bstree.contains(nodesVals[2]))
    {
        std::cout << "Contains " << nodesVals[2] << std::endl;
    }
    // else
    {
        std::cout << "Your algorithm doesn't work propely :(" << std::endl;
    }

    // if (!bstree.contains(-100))
    {
        std::cout << "There is no -100 in tree :)))" << std::endl;
    }

    std::cout << "[INFO] [insert(const Comparable &x)] [OK]\n"
              << std::endl;
}

void testMoveableInsert()
{
    std::cout << "*****"
              << "Testing moveable insert" << std::endl;

    // Create RNG
    std::mt19937 rng;
    // Init seed
    rng.seed(std::random_device()());
    // Set lower and upper bounds
    int lowerBound = 0, upperBound = 10;
    std::uniform_int_distribution<int> dist(lowerBound, upperBound);

    BST<int> bstree;
    // Set nodes count
    size_t nodeCount = 25;
    // Create some vector, for further tests
    std::vector<int> nodesVals;
    nodesVals.reserve(nodeCount);
    // Start to fill it
    for (size_t i = 0; i < nodeCount; ++i)
    {
        int value = dist(rng);
        nodesVals.push_back(value);
        std::cout << "IM HERE" << std::endl;
        bstree.insert(std::move(value));
    }

    if (bstree.contains(nodesVals[2]))
    {
        std::cout << "Contains " << nodesVals[2] << std::endl;
    }
    else
    {
        std::cout << "Your algorithm doesn't work propely :(" << std::endl;
    }

    if (!bstree.contains(-100))
    {
        std::cout << "There is no -100 in tree :)))" << std::endl;
    }

    std::cout << "[INFO] [insert(const Comparable &&x)] [OK]" << std::endl;
}

void testFindMin()
{
    std::cout << "*****"
              << "Testing minimum finding" << std::endl;
    // Create RNG
    std::mt19937 rng;
    // Init seed
    rng.seed(std::random_device()());
    // Set lower and upper bounds
    int lowerBound = 3, upperBound = 10;
    std::uniform_int_distribution<int> dist(lowerBound, upperBound);

    BST<int> bstree;
    // Set nodes count
    size_t nodeCount = 25;
    // Create some vector, for further tests
    std::vector<int> nodesVals;
    nodesVals.reserve(nodeCount);
    // Start to fill it
    for (size_t i = 0; i < nodeCount; ++i)
    {
        int value = dist(rng);
        nodesVals.push_back(value);
        bstree.insert(value);
    }

    auto min = bstree.findMin();
    std::cout << "minimum in tree: " << *min << std::endl;

    auto minVec = std::min_element(nodesVals.begin(), nodesVals.end());
    std::cout << "minimum in vector: " << *minVec << std::endl;

    std::cout << "\nPrinting vector: ";
    for (const auto &v : nodesVals)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    if (*min == *minVec)
    {
        std::cout << "OK, trees minimum equals to vectors minimum!" << std::endl;
    }

    std::cout << "[INFO] [insert(const Comparable &x)] [OK]\n"
              << std::endl;
}

void testFindMax()
{
    std::cout << "*****"
              << "Testing maximum finding" << std::endl;
    // Create RNG
    std::mt19937 rng;
    // Init seed
    rng.seed(std::random_device()());
    // Set lower and upper bounds
    int lowerBound = 3, upperBound = 10;
    std::uniform_int_distribution<int> dist(lowerBound, upperBound);

    BST<int> bstree;
    // Set nodes count
    size_t nodeCount = 25;
    // Create some vector, for further tests
    std::vector<int> nodesVals;
    nodesVals.reserve(nodeCount);
    // Start to fill it
    for (size_t i = 0; i < nodeCount; ++i)
    {
        int value = dist(rng);
        nodesVals.push_back(value);
        bstree.insert(value);
    }

    auto max = bstree.findMax();
    std::cout << "maximum in tree: " << *max << std::endl;

    auto maxVec = std::max_element(nodesVals.begin(), nodesVals.end());
    std::cout << "maximum in vector: " << *maxVec << std::endl;

    std::cout << "\nPrinting vector: ";
    for (const auto &v : nodesVals)
    {
        std::cout << v << ' ';
    }
    std::cout << std::endl;

    if (*max == *maxVec)
    {
        std::cout << "OK, trees maximum equals to vectors maximum!" << std::endl;
    }

    std::cout << "[INFO] [insert(const Comparable &x)] [OK]\n"
              << std::endl;
}

void testRemove()
{
    BST<int> bstree;
    bstree.insert(12);
    bstree.insert(1);
    bstree.insert(-4);
    bstree.insert(3);

    std::cout << (bstree.contains(-4) ? "Contains -4" : "Doesn't contains") << std::endl;
    bstree.remove(-4);
    std::cout << (bstree.contains(-4) ? "Contains -4" : "Doesn't contains") << std::endl;
}
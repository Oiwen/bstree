#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <random>
#include <algorithm>

#include "bst.h"

int main()
{
    std::fstream knuthWords("sgb-words.txt");
    if(!knuthWords.is_open()) {
        std::cerr << "Error opening ""sgb-words.txt""\n";
        return -1;
    }

   BST<std::string> bst;

    std::string word;
    std::size_t wordCount = 0;
    while(std::getline(knuthWords, word)) {
        if(word[0] == '#') {
          continue;
        }

        std::cout << "Word is: " << word << "\n";
        ++wordCount;
        bst.insert(word);
    }
    
    std::cout << "Word count is: " << wordCount << "\n";
    knuthWords.close();

    //word = "";
    //std::string option = "yes";
    //while(option == "yes" || option == "y") {
        //std::cout << "Enter word: ";
        //std::cin >> word;

        //if(bst.contains(word)) {
            //std::cout << "Contains word: " << word << "\n";
        //}

        //std::cout << "Continue(\\y\\es): ";
        //std::cin >> option;
    //}

    bst.levelorder_iterative();

    return 0;
}


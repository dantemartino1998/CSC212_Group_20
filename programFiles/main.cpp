#include "splaytree.h"
#include <iostream>
#include <fstream>
#include <sstream>

int main(int argc, char* argv[]) { //handles command line argument. requires input file to run
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl; //if no input file is provided
        return 1;
    }

    SplayTree splayTree;
    std::ifstream inputFile(argv[1]);

    if (inputFile.is_open()) { //reads input file and adds words to the Splay Tree
        std::string word;
        while (inputFile >> word) {
            splayTree.insert(word);
        }

        inputFile.close(); //closes input file
    } else {
        std::cerr << "Error: Unable to open input file." << std::endl; //error handling
        return 1;
    }

    //menu for user to pick operation goes here. this loop continues until user inputs option 3.


    
}

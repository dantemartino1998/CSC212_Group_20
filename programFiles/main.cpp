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
    while (true) {
        std::cout << "Choose an operation:" << std::endl;
        std::cout << "1. Search for an element" << std::endl;
        std::cout << "2. Insert an element" << std::endl;
        std::cout << "3. Quit" << std::endl;

        int choice;
        std::cin >> choice; //takes user input for which operation to do

        if (choice == 1) {
            //search operation
            std::string target;
            std::cout << "Enter a word to search (or 'q' to go back to the menu): ";
            std::cin >> target;

            if (target == "q") { //goes back to menu if user inputs q
                continue;
            }

            auto result = splayTree.search(target); //perform search in Splay Tree for entered word
            if (result.first) {//if word is found, display the word and its current count.
                std::cout << "Found \"" << target << "\" in the tree. Count: " << result.second << std::endl;
            } else {//if word isn't found, prints message.
                std::cout << "\"" << target << "\" not found in the tree." << std::endl;
            }
        } else if (choice == 2) {
            //insert operation
            std::string newWord;
            std::cout << "Enter a word to insert (or 'q' to go back to the menu): ";
            std::cin >> newWord;

            if (newWord == "q") {//enter q to quit
                continue;
            }

            splayTree.insert(newWord);//inserts word into Splay Tree
            std::cout << "\"" << newWord << "\" inserted into the tree." << std::endl;
        } else if (choice == 3) {
            //quit the program
            break;
        } else {//error handling for invalid choice.
            std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

        //generate DOT file for visualization after each operation
        splayTree.generateDotFile("splay_tree.dot");
    }
    
    return 0;
}

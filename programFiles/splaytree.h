#pragma once
#include <iostream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>

#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

class SplayNode
{
    private:
        std::string word; //word stored in node
        int count; //count of occurences of word
        SplayNode* left; //pointer to left child
        SplayNode* right; //pointer to right child

    public:
        SplayNode();
        SplayNode(std::string word);
        ~SplayNode();

    friend class SplayTree;
};

class SplayTree
{
    private:
        SplayNode* root; //pointer to root of splay tree
        SplayNode* zig(SplayNode* x);
        SplayNode* zag(SplayNode* x);
        SplayNode* splay(SplayNode* root, const std::string& target);
        SplayNode* insert(SplayNode* root, const std::string& word);
        void printTree(SplayNode* node, std::ostream& out);
    public:
        SplayTree();//constructor for SplayTree class
        ~SplayTree();
        void insert(const std::string& word);
        std::pair<bool, int> search(const std::string& target);
        void generateDotFile(const std::string& filename);
};

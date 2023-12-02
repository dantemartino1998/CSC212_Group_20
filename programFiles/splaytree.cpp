#include "splaytree.h"

//SplayNode classes
SplayNode::SplayNode(std::string word) {
   this->word = word;
   this->left = nullptr;
   this->right = nullptr;
   count = 1;
}

SplayNode::SplayNode(){ 
   this->word = nullptr;
   this->left = nullptr;
   this->right = nullptr;
   count = 0;
}

SplayNode::~SplayNode(){

}

SplayNode* SplayTree::zig(SplayNode* x) { //helper method for the zig rotation
   SplayNode* y = x->left;
   x->left = y->right;
   y->right = x;
   return y;
}

SplayNode* SplayTree::zag(SplayNode* x) { //helper method for the zag rotation
  
}

SplayNode* SplayTree::splay(SplayNode* root, const std::string& target) { //reorganizes tree to set new node to root/use zig/zags
   
}


SplayNode* SplayTree::insert(SplayNode* root, const std::string& newWord) { //inserts like normal BST2
   
}

void SplayTree::printTree(SplayNode* node, std::ostream& out) { //prints tree for DOT file
  
}

//SplayTree classes
SplayTree::SplayTree() {

}
SplayTree::~SplayTree() {

}

void SplayTree::insert(const std::string& newWord) {//public method for inserting word into tree
  
}

std::pair<bool, int> SplayTree::search(const std::string& target) {//method for searching for word in tree
    
}

void SplayTree::generateDotFile(const std::string& filename) { //makes dot file for display
   
}



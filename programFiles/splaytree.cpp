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
   SplayNode* y = x->left; //store left child of x in y
   x->left = y->right; //make right child of y the left child of x
   y->right = x; //make x the right child of y
   return y; //return new root, which is y
}

SplayNode* SplayTree::zag(SplayNode* x) { //helper method for the zag rotation
    SplayNode* y = x->right; //store right child of x in y
    x->right = y->left; //make the left child of y the right child of x
    y->left = x; //make x the left child of y
    return y; //return new root, which is y
}

SplayNode* SplayTree::splay(SplayNode* root, const std::string& target) { //reorganizes tree to set new node to root/use zig/zags
   
}


SplayNode* SplayTree::insert(SplayNode* root, const std::string& newWord) { //inserts like normal BST
     if(!root){
        return new SplayNode(newWord);
    }
    // if word is smaller, left
    if(newWord < root->word){
        root->left = insert(root->left,newWord);
        //otherwise right
    }else{
        root->right = insert(root->right,newWord);
    }
    return root;
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



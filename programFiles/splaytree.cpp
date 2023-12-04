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
   //if the current root is null or matches the searched word, no splaying/rotations needed, current root returned.
    if (!root || root->word == target) {
        return root;
    }
   if (target < root->word) {
        //if target is less than the current root's word, it means the target may be in the left subtree.
        //if there is no left child, no further splaying needed, and the current root is returned.
        if (!root->left) {
            return root;
        }

        if (target < root->left->word) {
            //if target is less than the current root, and there is a left child, further checks are performed on the left child.
            //if target is less than the left child's word, a recursive splay operation is performed on the left-left subtree,
            //applying a zig rotation.
            root->left->left = splay(root->left->left, target);
            root = zig(root);
        } else if (target > root->left->word) {
            //if target is greater than the left child's word, a recursive splay operation is performed on
            //the left-right subtree, and a zig rotation is applied if needed.
            root->left->right = splay(root->left->right, target);
            if (root->left->right) {
                root->left = zag(root->left);
            }
        }

        //a zig rotation is applied to the root if the left child is not null; otherwise, the current root is returned.
        return (root->left) ? zig(root) : root;
    } else {
        //if the target is greater than the current root's word, and there is a right child,
        //similar checks and operations are performed for the right subtree.
        if (!root->right) {
            return root;
        }

        if (target < root->right->word) {
            //if target is less than the right child's word, a recursive splay operation is performed on the right-left subtree,
            //and a zig rotation is applied if needed.
            root->right->left = splay(root->right->left, target);
            if (root->right->left) {
                root->right = zig(root->right);
            }
        } else if (target > root->right->word) {
            //if target is greater than the right child's word, a recursive splay operation is performed on the right-right subtree,
            //and a zag rotation is applied.
            root->right->right = splay(root->right->right, target);
            root = zag(root);
        }

        //finally, a zag rotation is applied to the root if the right child is not null; otherwise, the current root is returned.
        return (root->right) ? zag(root) : root;
    }
}


SplayNode* SplayTree::insert(SplayNode* root, const std::string& newWord) { //inserts like normal BST
     if(!root){
        return new SplayNode(newWord);
    }
    if (newWord == root->word) //if duplicate found, don't insert (wouldn't splay properly, extra couldnt be root)
    {
        root->count++; //augment count
        return root;
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
  //if the current node is not null (i.e., the tree is not empty),
    if (node) {
        //if there is a left child, print an edge from the current node to its left child with a label "L".
        if (node->left) {
            out << "\"" << node->word << "\" -> \"" << node->left->word << "\" [label=\"L\"]" << std::endl;
        }
        //if there is a right child, print an edge from the current node to its right child with a label "R".
        if (node->right) {
            out << "\"" << node->word << "\" -> \"" << node->right->word << "\" [label=\"R\"]" << std::endl;
        }
        //print the information of the current node, including its word, count, and a label for visualization.
        out << "\"" << node->word << "\" [label=\"" << node->word << "\\nCount: " << node->count << "\"]" << std::endl;
        //recursively call printTree on the left and right subtrees to print their nodes and edges.
        printTree(node->left, out);
        printTree(node->right, out);
    }
}

//SplayTree constructor
SplayTree::SplayTree() {
    root = nullptr;
}
SplayTree::~SplayTree() {
//left blank
}

void SplayTree::insert(const std::string& newWord) {//public method for inserting word into tree
    root = insert(root, newWord);//calls private insert method, passes current root and word to be inserted
    root = splay(root, newWord);
}

std::pair<bool, int> SplayTree::search(const std::string& target) {//method for searching for word in tree
        root = splay(root, target);//splays the tree to bring potential target or closet ancestor to the root

    if (root->word == target) {//checks if the root word matches target
        return {true, root->count};//if word is found, return true and count of found word
    } else {
        return {false, 0};//word not found, return false and count of 0
    }
}

void SplayTree::generateDotFile(const std::string& filename) { //makes dot file for display
   std::ofstream dotFile(filename);

//checks if the file was opened succesfully
if (dotFile.is_open()) {

    //write initial line for DOT format indicating it is a directed graph names SplayTree
    dotFile << "digraph SplayTree {" << std::endl;

    //call the printTree function to recursively print the nodes and edges of the Splay Tree
    printTree(root, dotFile);

    //writes closing bracked to end the DOT file
    dotFile << "}" << std::endl;

    //close DOT file
    dotFile.close();

    //prints if file was generated or failed
    std::cout << "DOT file generated: " << filename << std::endl;
} else {
    std::cerr << "Error: Unable to open DOT file for writing." << std::endl;
}
}



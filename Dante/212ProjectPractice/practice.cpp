#include <iostream>
#include <vector>

struct Node {
    int data;
    Node* left;
    Node* right;
};

class SplayTree {
private:
    Node* root;

    // Perform Zig rotation
    Node* zig(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // Perform Zag rotation
    Node* zag(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Splay operation to bring the target element to the root
    Node* splay(Node* root, int target) {
        if (!root || root->data == target) {
            return root;
        }

        if (target < root->data) {
            if (!root->left) {
                return root;
            }

            if (target < root->left->data) {
                root->left->left = splay(root->left->left, target);
                root = zig(root);
            } else if (target > root->left->data) {
                root->left->right = splay(root->left->right, target);
                if (root->left->right) {
                    root->left = zag(root->left);
                }
            }

            return (root->left) ? zig(root) : root;
        } else {
            if (!root->right) {
                return root;
            }

            if (target < root->right->data) {
                root->right->left = splay(root->right->left, target);
                if (root->right->left) {
                    root->right = zig(root->right);
                }
            } else if (target > root->right->data) {
                root->right->right = splay(root->right->right, target);
                root = zag(root);
            }

            return (root->right) ? zag(root) : root;
        }
    }

    // Print the tree structure
    void printTree(Node* node, int depth = 0) {
        if (node) {
            printTree(node->right, depth + 1);
            for (int i = 0; i < depth; ++i) {
                std::cout << "    ";
            }
            std::cout << node->data << std::endl;
            printTree(node->left, depth + 1);
        }
    }

    // Helper function to build a balanced tree from a sorted array
    Node* buildBalancedTree(std::vector<int>& elements, int start, int end) {
        if (start > end) {
            return nullptr;
        }

        int mid = (start + end) / 2;
        Node* newNode = new Node{elements[mid], nullptr, nullptr};
        newNode->left = buildBalancedTree(elements, start, mid - 1);
        newNode->right = buildBalancedTree(elements, mid + 1, end);
        return newNode;
    }

public:
    SplayTree() : root(nullptr) {}

    void insertBalanced(std::vector<int>& elements) {
        root = buildBalancedTree(elements, 0, elements.size() - 1);
    }


    void insert(int data) {
        if (!root) {
            root = new Node{data, nullptr, nullptr};
        } else {
            root = splay(root, data);
            if (data < root->data) {
                Node* newNode = new Node{data, root->left, root};
                root->left = nullptr;
                root = newNode;
            } else if (data > root->data) {
                Node* newNode = new Node{data, root, root->right};
                root->right = nullptr;
                root = newNode;
            }
        }
    }

    void search(int target) {
        if (!root) {
            std::cout << "The tree is empty." << std::endl;
            return;
        }

        root = splay(root, target);

        if (root->data == target) {
            std::cout << "Found " << target << " in the tree." << std::endl;
        } else {
            std::cout << target << " not found in the tree." << std::endl;
        }

        std::cout << "Current Splay Tree:" << std::endl;
        printTree(root);
    }
    void printStartingTree() {
        std::cout << "Starting Splay Tree:" << std::endl;
        printTree(root);
    }
};

int main(int argc, char* argv[]) {
    SplayTree splayTree;
    std::vector<int> elements;

    // Parse command line arguments and add them to the elements vector
    for (int i = 1; i < argc; i++) {
        int data = std::stoi(argv[i]);
        elements.push_back(data);
    }

    // Insert elements in a balanced order
    splayTree.insertBalanced(elements);

    // Print the starting tree
    splayTree.printStartingTree();

    while (true) {
        int target;
        std::cout << "Enter an element to search (or 'q' to quit): ";
        std::string input;
        std::cin >> input;

        if (input == "q") {
            break;
        }

        try {
            target = std::stoi(input);
            splayTree.search(target);
        } catch (std::invalid_argument& e) {
            std::cout << "Invalid input. Please enter a valid number or 'q' to quit." << std::endl;
        }
    }

    return 0;
}

#include "AVLTree.h"
#include <iostream>
#include <fstream>
#include <sstream>

//constructor of the avltree
AVLTree::AVLTree() : root(nullptr), size(0) {}
//destructor
AVLTree::~AVLTree() {
    destroyTree(root);
}
//destroys all the nodes of the tree
void AVLTree::destroyTree(Node* node) {
    if (node) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
//returns the height of the tree
int AVLTree::getHeight(Node* node) {
    return node ? node->height : 0;
}
//gets the balance of a node
int AVLTree::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
//gets the maximum of two int
int AVLTree::max(int a, int b) {
    return (a > b) ? a : b;
}
//performs a left rotation in the avltree
AVLTree::Node* AVLTree::rotateLeft(Node* x) {
    //performs the rotation
    Node* y = x->right;
    Node* T2 = y->left;
    //updating the height and returns the new root
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}
//performs a right rotation in the avltree
AVLTree::Node* AVLTree::rotateRight(Node* y) {
    //performs rotation
    Node* x = y->left;
    Node* T2 = x->right;
    //updating the height and returns the new root
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}
//function to insert a key in the subtree rooted with node and returns the new root of the subtree
AVLTree::Node* AVLTree::insert(Node* node, int key) {
    //BTS rotation
    if (!node) {
        size++;
        return new Node{key, nullptr, nullptr, 1};
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        return node;
    }
     //updates height of this ancestor node
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    //gets the balance of this ancestor node
    int balance = getBalance(node);
    //if the tree is unbalanced there are 4 possible cases
    if (balance > 1 && key < node->left->key)
        return rotateRight(node);

    if (balance < -1 && key > node->right->key)
        return rotateLeft(node);

    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}
//public insertion function
void AVLTree::insert(int key) {
    root = insert(root, key);
}
//function to delete a node with a given key from subtree with given root
AVLTree::Node* AVLTree::deleteNode(Node* root, int key) {
    //performs BTS delete
    if (!root) return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((!root->left) || (!root->right)) {
            Node* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;

            delete temp;
            size--;
        } else {
            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (!root) return root;
    //updates the height
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalance(root);
    //if the node is unbalanced there are 4 possible cases
    if (balance > 1 && getBalance(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
//public delete function
void AVLTree::deleteNode(int key) {
    root = deleteNode(root, key);
}
//finds minimum key value in the tree
AVLTree::Node* AVLTree::findMin(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}
// public function that finds and returns the minimum key in the tree
int AVLTree::findMin() {
    if (!root) {
        std::cerr << "The tree is empty.\n";
        return -1;
    }
    return findMin(root)->key;
}
//public function that search a key in the tree
bool AVLTree::search(int key) {
    return search(root, key) != nullptr;
}
//search function
AVLTree::Node* AVLTree::search(Node* node, int key) {
    if (!node || node->key == key)
        return node;
    if (key < node->key)
        return search(node->left, key);
    return search(node->right, key);
}
//gets the size of the avltree
int AVLTree::getSize() {
    return size;
}
//builds the avltree from the given file
void AVLTree::buildFromFile(int* data, int length) {
    for (int i = 0; i < length; ++i) {
        insert(data[i]);
    }
}

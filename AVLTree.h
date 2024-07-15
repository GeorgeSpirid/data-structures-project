#ifndef AVLTREE_H
#define AVLTREE_H

class AVLTree {

private:
    //struct for a node in the avltree
    struct Node {
        int key;
        Node* left;
        Node* right;
        int height;
    };

    Node* root;
    int size;

    Node* insert(Node* node, int key);//insert the node
    Node* deleteNode(Node* node, int key);//delete the node
    Node* findMin(Node* node);//find the minimum node
    Node* search(Node* node, int key);//searching a node in the tree
    Node* rotateLeft(Node* x);//left rotation
    Node* rotateRight(Node* y);//right rotation
    int getHeight(Node* node);//gets the height of the node
    int getBalance(Node* node);//gets the balance of the node
    void destroyTree(Node* node);//destroys the avltree
    int max(int a, int b);

public:
    AVLTree();//constructor for the tree
    ~AVLTree();//destructor
    void setData(int *data,int length);//sets the data from the file
    int* getData();//gets the data from the file
    void insert(int key);//insertion in the avltree
    void deleteNode(int key);//deletes a node
    int findMin();//finds minimum node
    bool search(int key);//searches for a key in the tree
    int getSize();//gets the size of the avltree
    void buildFromFile(int* data, int length);//builds the avltree from the given file
};

#endif

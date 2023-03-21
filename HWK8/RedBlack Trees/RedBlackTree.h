#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

enum Color {
    RED,
    BLACK
};

struct Node {
    int key;
    Color color;
    Node *left, *right, *parent;

    Node(int key) {
        this->key = key;
        color = RED;
        left = right = parent = NULL;
    }
};

class RedBlackTree {
private:
    Node *root;

    void leftRotate(Node *x);
    void rightRotate(Node *y);
    void fixInsert(Node *z);
    void transplant(Node *u, Node *v);
    void fixDelete(Node *x);

    void inOrderTraversal(Node *x);
    Node *findMin(Node *x);
    Node *findMax(Node *x);
    Node *successor(Node* x);
    Node *predecessor(Node* key);
    int getHeight(Node *x);

public:
    RedBlackTree();
    Node *search(int key);
    void insert(int key);
    void remove(int key);
    void sort();
    void findMin();
    void findMax();
    void findSuccessor(int key);
    void findPredecessor(int key);
    void printHeight();
};

#endif

#include <bits/stdc++.h>

using namespace std;

class BinomialNode {
public:
    int key;
    BinomialNode* parent;
    BinomialNode* child;
    BinomialNode* sibling;

    BinomialNode(int key) {
        this->key = key;
        parent = NULL;
        child = NULL;
        sibling = NULL;
    }
};

class BinomialHeap {
public:
    BinomialNode* head;

    BinomialHeap() {
        head = NULL;
    }

    BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2);
    BinomialNode* reverse(BinomialNode* node);
    BinomialNode* findMinimum();
    BinomialNode* makeHeap(int key);
    BinomialNode* insert(int key);
    int extractMin();
    BinomialNode* unionHeaps(BinomialHeap& otherHeap);
    BinomialNode* decreaseKey(BinomialNode* node, int newKey);
    int deleteNode(BinomialNode* node);
    void levelOrderTraversal();
};

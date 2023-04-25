#include "BinomialHeap.h"

BinomialNode* BinomialHeap::mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;

    BinomialNode* mergedHeap;

    if (h1->key <= h2->key) {
        mergedHeap = h1;
        h1 = h1->sibling;
    } else {
        mergedHeap = h2;
        h2 = h2->sibling;
    }

    BinomialNode* curr = mergedHeap;

    while (h1 && h2) {
        if (h1->key <= h2->key) {
            curr->sibling = h1;
            h1 = h1->sibling;
        } else {
            curr->sibling = h2;
            h2 = h2->sibling;
        }
        curr = curr->sibling;
    }

    if (h1) curr->sibling = h1;
    if (h2) curr->sibling = h2;

    return mergedHeap;
}

BinomialNode* BinomialHeap::reverse(BinomialNode* node) {
    BinomialNode* prev = NULL;
    BinomialNode* curr = node;
    BinomialNode* next = NULL;

    while (curr) {
        next = curr->sibling;
        curr->sibling = prev;
        prev = curr;
        curr = next;
    }

    return prev;
}

BinomialNode* BinomialHeap::findMinimum() {
    if (!head) return NULL;

    BinomialNode* curr = head;
    BinomialNode* minNode = head;

    while (curr->sibling) {
        if (curr->sibling->key < minNode->key) {
            minNode = curr->sibling;
        }
        curr = curr->sibling;
    }

    return minNode;
}

BinomialNode* BinomialHeap::makeHeap(int key) {
    BinomialNode* node = new BinomialNode(key);
    head = node;
    return head;
}

BinomialNode* BinomialHeap::insert(int key) {
    BinomialHeap newHeap;
    BinomialNode* newNode = new BinomialNode(key);
    newHeap.head = newNode;
    BinomialNode* mergedHeap = mergeHeaps(head, newHeap.head);
    head = mergedHeap;
    return newNode;
}


int BinomialHeap::extractMin() {
    if (!head) return INT_MAX;
    BinomialNode* curr = head;
    BinomialNode* prev = NULL;
    BinomialNode* minNode = findMinimum();

    while (curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }

    if (curr == head) {
        head = curr->sibling;
    } else {
        prev->sibling = curr->sibling;
    }

    BinomialNode* newHead = reverse(minNode->child);
    BinomialHeap newHeap;
    newHeap.head = newHead;
    head = mergeHeaps(head, newHeap.head);

    int minKey = minNode->key;
    delete minNode;

    return minKey;
}

BinomialNode* BinomialHeap::unionHeaps(BinomialHeap& otherHeap) {
    BinomialNode* mergedHeap = mergeHeaps(head, otherHeap.head);
    head = NULL;
    otherHeap.head = NULL;
    head = mergedHeap;
    return head;
}

BinomialNode* BinomialHeap::decreaseKey(BinomialNode* node, int newKey) {
    if (!node || newKey > node->key) return NULL;
    node->key = newKey;
    BinomialNode* curr = node;
    BinomialNode* parent = curr->parent;

    while (parent && curr->key < parent->key) {
        swap(curr->key, parent->key);
        curr = parent;
        parent = curr->parent;
    }

    return node;
}

int BinomialHeap::deleteNode(BinomialNode* node) {
    decreaseKey(node, INT_MIN);
    return extractMin();
}

// void BinomialHeap::levelOrderTraversal() {
//     if (!head) return;
//     vector<BinomialNode*> queue;
//     queue.push_back(head);
//     int l = 0;
//     while (!queue.empty()) {
//         BinomialNode* curr = queue.front();
//         queue.erase(queue.begin());
//         cout<<"Level: "<< l++<< " ";
//         while (curr) {
//             cout << curr->key << " ";
//             if (curr->child) {
//                 queue.push_back(curr->child);
//             }
//             curr = curr->sibling;
//         }
//     }
//     cout << endl;
// }

void BinomialHeap::levelOrderTraversal() {
    if (head == nullptr) {
        return;
    }
    queue<pair<BinomialNode*, int>> q;  // pair of (node, level)
    q.push(make_pair(head, 0));
    int curLevel = -1;
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        auto node = p.first;
        int level = p.second;
        if (level > curLevel) {
            curLevel = level;
            cout << "Level " << curLevel << ": ";
        }
        cout << node->key << " ";
        if (node->child != nullptr) {
            q.push(make_pair(node->child, level + 1));
        }
        if (node->sibling != nullptr) {
            q.push(make_pair(node->sibling, level));
        }
    }
    cout << endl;
}




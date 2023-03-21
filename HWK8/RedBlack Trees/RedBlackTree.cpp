#include "RedBlackTree.h"

RedBlackTree::RedBlackTree() {
    root = NULL;
}

void RedBlackTree::leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;

    if (x->parent == NULL)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlackTree::rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void RedBlackTree::fixInsert(Node *z) {
    while (z != root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            Node *y = z->parent->parent->right;
            if (y != NULL && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            Node *y = z->parent->parent->left;
            if (y != NULL && y->color == RED) {
            z->parent->color = BLACK;
            y->color = BLACK;
            z->parent->parent->color = RED;
            z = z->parent->parent;
        } 
        else {
            if (z == z->parent->left) {
                z = z->parent;
                rightRotate(z);
            }
            z->parent->color = BLACK;
            z->parent->parent->color = RED;
            leftRotate(z->parent->parent);
        }
    }
    }
    root->color = BLACK;
}

void RedBlackTree::transplant(Node *u, Node *v) {
    if (u->parent == NULL)
    root = v;
    else if (u == u->parent->left)
    u->parent->left = v;
    else
    u->parent->right = v;
    v->parent = u->parent;
}

void RedBlackTree::fixDelete(Node *x) {
while (x != root && x->color == BLACK) {
    if (x == x->parent->left) {
            Node *w = x->parent->right;
            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                leftRotate(x->parent);
                w = x->parent->right;
            }
            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } 
            else {
            if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = x->parent->right;
            }
            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            leftRotate(x->parent);
            x = root;
            }
        } 
    else {
        Node *w = x->parent->left;
        if (w->color == RED) {
            w->color = BLACK;
            x->parent->color = RED;
            rightRotate(x->parent);
            w = x->parent->left;
        }
        if (w->right->color == BLACK && w->left->color == BLACK) {
            w->color = RED;
            x = x->parent;
        } else {
        if (w->left->color == BLACK) {
            w->right->color = BLACK;
            w->color = RED;
            leftRotate(w);
            w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
        }
    }
    }
    x->color = BLACK;
}

void RedBlackTree::insert(int key) {
Node *z = new Node(key);
Node *y = NULL;
Node *x = root;
while (x != NULL) {
    y = x;
    if (z->key < x->key)
        x = x->left;
    else
        x = x->right;
}

z->parent = y;
if (y == NULL)
    root = z;
else if (z->key < y->key)
    y->left = z;
else
    y->right = z;

fixInsert(z);
}

void RedBlackTree::remove(int key) {
    Node* z = search(key);
    if (z == NULL) {
        cout<<"\n\nThe key does not exist.";
    }
    Node *x, *y;
    if (z->left == NULL || z->right == NULL)
        y = z;
    else
        y = successor(z);
    if (y->left != NULL)
        x = y->left;
    else
        x = y->right;

    if (x != NULL)
        x->parent = y->parent;

    if (y->parent == NULL)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    if (y != z)
        z->key = y->key;

    if (y->color == BLACK)
        fixDelete(x);

    delete y;
}

/*
void RedBlackTree::fixDelete(Node *x) {
while (x != root && x->color == BLACK) {
if (x == x->parent->left) {
Node *w = x->parent->right;
if (w->color == RED) {
w->color = BLACK;
x->parent->color = RED;
leftRotate(x->parent);
w = x->parent->right;
}
        if (w->left->color == BLACK && w->right->color == BLACK) {
            w->color = RED;
            x = x->parent;
        } else {
            if (w->right->color == BLACK) {
                w->left->color = BLACK;
                w->color = RED;
                rightRotate(w);
                w = x->parent->right;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->right->color = BLACK;
            leftRotate(x->parent);
            x = root;
        }
    } else {
        Node *w = x->parent->left;
        if (w->color == RED) {
            w->color = BLACK;
            x->parent->color = RED;
            rightRotate(x->parent);
            w = x->parent->left;
        }

        if (w->left->color == BLACK && w->right->color == BLACK) {
            w->color = RED;
            x = x->parent;
        } else {
            if (w->left->color == BLACK) {
                w->right->color = BLACK;
                w->color = RED;
                leftRotate(w);
                w = x->parent->left;
            }

            w->color = x->parent->color;
            x->parent->color = BLACK;
            w->left->color = BLACK;
            rightRotate(x->parent);
            x = root;
        }
    }
}
x->color = BLACK;
}
*/

Node *RedBlackTree::search(int key) {
    Node *temp = root;
    while (temp != NULL && temp->key != key) {
    if (key < temp->key)
    temp = temp->left;
    else
    temp = temp->right;
    }
    return temp;
}

Node *RedBlackTree::findMin(Node *node) {
    Node *temp = node;
    while (temp->left != NULL)
    temp = temp->left;
    return temp;
}

Node *RedBlackTree::findMax(Node *node) {
    Node *temp = node;
    while (temp->right != NULL)
    temp = temp->right;
    return temp;
}

int RedBlackTree::getHeight(Node *x) {
    if (!x) {
        return -1;
    } else {
        int leftHeight = getHeight(x->left);
        int rightHeight = getHeight(x->right);
        return std::max(leftHeight, rightHeight) + 1;
    }
}


void RedBlackTree::findMin(){
    if (root == NULL) {
        cout<<"\nTree empty";
        return;
    }
    Node* node = findMin(root);
    if (node != NULL) {
        cout<<"\nMinimum value in the tree is:"<< node -> key;
    }
    else {
        cout<<"\nThe tree is empty";
    }
}

void RedBlackTree::findMax(){
    if (root == NULL) {
        cout<<"\nTree empty";
        return;
    }
    Node* node = findMax(root);
    if (node != NULL) {
        cout<<"\nMaximum value in the tree is:"<< node -> key;
    }
    else {
        cout<<"\nThe tree is empty";
    }
}

void RedBlackTree::printHeight() {
    if (root == NULL) {
        cout<<"\nTree empty";
        return;
    }
    int height = getHeight(root);
    if(height == -1) {
        cout<<"\nThe tree is empty";
    }
    else {
        cout<<"\nThe height of the tree is: "<< height;
    }
}

Node *RedBlackTree::successor(Node *node) {
    if (node->right != NULL)
        return findMin(node->right);
    else {
        Node *y = node->parent;
        while (y && node == y->right) {
            node = y;
            y = y->parent;
        }
        return y;
    }
}

Node *RedBlackTree::predecessor(Node *node) {
    if (node->left != NULL)
        return findMax(node->left);
    Node *temp = node->parent;
    while (temp != NULL && node == temp->left) {
        node = temp;
        temp = temp->parent;
    }
    return temp;
}

void RedBlackTree::findSuccessor(int key) {
    Node* node = search(key);
    if (node != NULL) {
        Node* succ = successor(node);
        if( succ != NULL) {
            cout<<"\nThe Successor of "<< key << " is : " << succ->key;
        }
        else {
            cout<<"\nNo successor for requested key";
        }
    }
    else {
        cout<<"\nThe requested key does not exist";
    }
}

void RedBlackTree::findPredecessor(int key) {
    Node* node = search(key);
    if (node != NULL) {
        Node* succ = predecessor(node);
        if( succ != NULL) {
            cout<<"\nThe Predecessor of "<< key << " is : " << succ->key;
        }
        else {
            cout<<"\nNo predecessor for requested key";
        }
    }
    else {
        cout<<"\nThe requested key does not exist";
    }
}

void RedBlackTree::sort() {
    inOrderTraversal(root);
}

void RedBlackTree::inOrderTraversal(Node *node) {
    if (node == NULL)
    return;
    inOrderTraversal(node->left);
    string color = node->color == 0 ? "Red":"Black" ;
    std::cout << "( " << node->key << " ," << color << " )" << endl;
    inOrderTraversal(node->right);
}


#include "RedBlackTree.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    RedBlackTree tree;
    ifstream input("input.txt");
    if (!input) {
    cout << "File not found!" << endl;
    return 0;
    }

    int x;
    while (input >> x)
        tree.insert(x);

    input.close();

    string command;
    int key;
    cout << "\nCommands: insert x, delete x, sort, search x, min, max, successor x, predecessor x, exit" << endl;
    while (true) {
        cout << "\n\nEnter command: ";
        cin >> command;

        if (command == "exit")
            break;
        else if (command == "insert") {
            cin >> key;
            tree.insert(key);
            tree.printHeight();
        } else if (command == "delete"){
            cin>>key;
            tree.remove(key);
            tree.printHeight();
        }else if (command == "sort") {
            tree.sort();
            tree.printHeight();
        } else if (command == "search") {
            cin >> key;
            Node* node = tree.search(key);
            if (node == NULL) {
                cout<<"\nNode with requested key found";
            }
            else {
                cout<<"\nNode with requested key does not exist";
            }
            // tree.printHeight();
        } else if (command == "min") {
            tree.findMin();
            tree.printHeight();
        } else if (command == "max") {
            tree.findMax();
            tree.printHeight();
        } else if (command == "successor") {
            cin >> key;
            tree.findSuccessor(key);
            tree.printHeight();
        } else if (command == "predecessor") {
            cin >> key;
            tree.findPredecessor(key);
            tree.printHeight();
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
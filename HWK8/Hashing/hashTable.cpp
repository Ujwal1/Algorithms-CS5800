/*
* hashTable.cpp 
* Ujwal Gupta
*/
#include "hashTable.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

Node::Node(const std::string& key, int value) {
    this->key = key;
    this->value = value;
    next = NULL;
}

HashTable::HashTable() {
}

HashTable::~HashTable() {
    for (int i = 0; i < MAXHASH; i++) {
        Node* node = buckets[i];
        while (node != NULL) {
            Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
}

int HashTable::hash(const std::string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 29 + c) % MAXHASH;
    }
    return hash;
}

void HashTable::insert(const std::string& key, int value) {
    int index = hash(key);
    Node* node = buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            node->value += value;
            return;
        }
        node = node->next;
    }
    Node* newNode = new Node(key, value);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    count++;
    // cout<<"Count" << count << " ";
}

void HashTable::remove(const std::string& key) {
    int index = hash(key);
    Node* node = buckets[index];
    Node* prev = NULL;
    while (node != NULL) {
        if (node->key == key) {
            if (prev == NULL) {
                buckets[index] = node->next;
            } else {
                prev->next = node->next;
            }
            delete node;
            count--;
            return;
        }
        prev = node;
        node = node->next;
    }
}

void HashTable::increase(const std::string& key) {
    int index = hash(key);
    Node* node = buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            node->value++;
            return;
        }
        node = node->next;
    }
}

int HashTable::find(const std::string& key) {
    int index = hash(key);
    Node* node = buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return 0;
}

void HashTable::listAllKeys() {
    for (int i = 0; i < MAXHASH; i++) {
            Node* node = buckets[i];
    while (node != NULL) {
        std::cout << node->key << " : " << node->value << std::endl;
        node = node->next;
    }
    }
}

void HashTable::outputToFile(const std::string& filename) {
    std::ofstream outfile(filename.c_str());
    if (outfile.is_open()) {
        for (int i = 0; i < MAXHASH; i++) {
            Node* node = buckets[i];
            while (node != NULL) {
                outfile << node->key << " : " << node->value << std::endl;
                node = node->next;
            }
        }
        outfile.close();
    } else {
        std::cout << "Error: could not open file " << filename << std::endl;
    }
}

int HashTable::getCount() const{
    return count;
}

Node* HashTable::getBucket(int index) const {
    if (index < 0 || index >= getCount()) {
        return NULL;
    }
    return buckets[index];
}

vector<pair<int, int> > HashTable::getBucketSizes() {
    vector<pair<int, int> > bucketSizes;
    for (int i = 0; i < MAXHASH; i++) {
        int a = 0;
        Node* node = buckets[i];
        while(node != NULL) {
            a += node->value;
            node = node->next;
        }
        bucketSizes.push_back(make_pair(i,a));
    }
    return bucketSizes;
}

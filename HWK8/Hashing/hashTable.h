/*
* Hashtable.h
* Ujwal Gupta
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <bits/stdc++.h>

using namespace std;

const int MAXHASH = 300;

class Node {
public:
    std::string key;
    int value;
    Node* next;
    Node(const std::string& key, int value);
};

class HashTable {
public:
    Node* buckets[MAXHASH] = { NULL };
    int count = 0;
    int hash(const std::string& key);
public:
    HashTable();
    ~HashTable();
    void insert(const std::string& key, int value);
    void remove(const std::string& key);
    void increase(const std::string& key);
    int find(const std::string& key);
    void listAllKeys();
    void outputToFile(const std::string& filename);
    int getCount() const;

    // getters
    Node* getBucket(int index) const;
    vector<pair<int,int> > getBucketSizes();
};

#endif

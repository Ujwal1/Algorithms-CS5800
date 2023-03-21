/*
* hash.cpp
* Ujwal Gupta
*/
#include "hashTable.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

double variance_calc(int sum, int n, vector<pair<int, int> > bucketSizes) {
    // cout<<"In variance:"<< sum <<" "<< n;
    double mean = (double)sum / (double)n;
    // cout<<"Mean="<<mean;
    double sqDiff = 0;
    for(int i = 0; i<n; i++) {
        // cout<<endl<< bucketSizes[i].second;
        sqDiff += (bucketSizes[i].second - mean) * (bucketSizes[i].second - mean) ;
    }
    // cout<<"SQDiff:"<<sqDiff;
    return sqDiff/(double)(n);
}

int main() {
    HashTable hashTable;

    // Read text file and insert words into hash table
    string filename = "Alice.txt";
    fstream inFile;
    inFile.open(filename.c_str());
    string line, word;

     while (inFile >> word)
    {
        // displaying content
        // cout << word << i++ << endl;
        hashTable.insert(word, 1);
    }

    while (std::getline(inFile, line)) {
        std::cout<<"Here";
        std::stringstream ss(line);
        while (ss >> word) {
            hashTable.insert(word, 1);
            cout<<"Here";
        }
    }

    // Output word counts to file
    std::ofstream outFile("word_counts.txt");
    for (int i = 0; i < MAXHASH; i++) {
        Node* node = hashTable.buckets[i];
        while (node != NULL) {
            outFile << node->key << " : " << node->value << std::endl;
            node = node->next;
        }
    }
    outFile.close();

    // Test operations on hash table
    std::cout << "Count of 'Alice': " << hashTable.find("Alice") << std::endl;
    hashTable.increase("Alice");
    std::cout << "Count of 'Alice' after increase: " << hashTable.find("Alice") << std::endl;
    // hashTable.decrease("Alice");
    // std::cout << "Count of 'Alice' after decrease: " << hashTable.find("Alice") << std::endl;
    hashTable.remove("Alice");
    std::cout << "Count of 'Alice' after removal: " << hashTable.find("Alice") << std::endl;

    // std::cout << "All keys:" << std::endl;
    // hashTable.listAllKeys();
    cout<<"\n Hash no : No of collisions";
    cout<<"\n---------------------------\n";
    vector<pair<int, int> > bucketSizes = hashTable.getBucketSizes();
    int sum = 0;
    for(auto a: bucketSizes) {
        cout<<endl<<a.first<<" : "<<a.second;
        sum += a.second;
    }

    double variance = variance_calc(sum, bucketSizes.size(), bucketSizes); 
    cout<<endl<<"Mean: "<< sum/bucketSizes.size();
    cout<<endl<<"Variance: "<<variance;
    cout<<endl<<"Standard Deviation: "<<sqrt(variance);

    sort(bucketSizes.begin(), bucketSizes.end(), [](const std::pair<int,int> &left, const std::pair<int,int> &right) {
    return left.second > right.second;
    });

    int n = bucketSizes.size();
    int m = n/10;
    cout<<"\n\nTop 10 percent lenght lists:\n";
    cout<<"\n Hash no : No of collisions";
    cout<<"\n---------------------------\n";
    for(int i = 0; i < m; i++) {
        cout<<endl<<bucketSizes[i].first<<" : "<<bucketSizes[i].second;
    }

    return 0;
}



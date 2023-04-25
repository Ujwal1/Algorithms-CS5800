#include "BinomialHeap.h"

using namespace std;

int main() {
    srand(time(NULL));

    BinomialHeap heap;

    // Insert 10 random keys into heap
    for (int i = 0; i < 10; i++) {
        int key = rand() % 100;
        heap.insert(key);
    }

    // Print heap before extraction
    cout << "Heap before extraction:" << endl;
    heap.levelOrderTraversal();

    // Extract minimum key until heap is empty
    while (heap.head) {
        int minKey = heap.extractMin();
        cout << "Extracted minimum key: " << minKey << endl;
        cout << "Heap after extraction:" << endl;
        heap.levelOrderTraversal();
    }

    return 0;
}

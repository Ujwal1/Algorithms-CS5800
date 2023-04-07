//package src;

import java.util.LinkedList;
import java.util.Queue;


public class BinomialHeap {
  public BinomialHeapNode Nodes;
  private int size;


  public BinomialHeap() {
    Nodes = null;
    size = 0;
  }


  public boolean isEmpty() {
    return Nodes == null;
  }


  public int getSize() {
    return size;
  }


  public void makeEmpty() {
    Nodes = null;
    size = 0;
  }

  public void insert(int value) {
    if (value > 0) {
      BinomialHeapNode temp
              = new BinomialHeapNode(value);
      if (Nodes == null) {
        Nodes = temp;
        size = 1;
      } else {
        union(temp);
        size++;
      }
    }
  }


  private void merge(BinomialHeapNode binHeap) {
    BinomialHeapNode temp1 = Nodes, temp2 = binHeap;

    while ((temp1 != null) && (temp2 != null)) {
      if (temp1.degree == temp2.degree) {
        BinomialHeapNode tmp = temp2;
        temp2 = temp2.rightSibling;
        tmp.rightSibling = temp1.rightSibling;
        temp1.rightSibling = tmp;
        temp1 = tmp.rightSibling;
      } else {
        if (temp1.degree < temp2.degree) {
          if ((temp1.rightSibling == null)
                  || (temp1.rightSibling.degree
                  > temp2.degree)) {
            BinomialHeapNode tmp = temp2;
            temp2 = temp2.rightSibling;
            tmp.rightSibling = temp1.rightSibling;
            temp1.rightSibling = tmp;
            temp1 = tmp.rightSibling;
          } else {
            temp1 = temp1.rightSibling;
          }
        } else {
          BinomialHeapNode tmp = temp1;
          temp1 = temp2;
          temp2 = temp2.rightSibling;
          temp1.rightSibling = tmp;

          if (tmp == Nodes) {
            Nodes = temp1;
          }
        }
      }
    }

    if (temp1 == null) {
      temp1 = Nodes;

      while (temp1.rightSibling != null) {
        temp1 = temp1.rightSibling;
      }
      temp1.rightSibling = temp2;
    }
  }


  public void union(BinomialHeapNode binHeap) {
    merge(binHeap);

    BinomialHeapNode prevTemp = null, temp = Nodes,
            nextTemp = Nodes.rightSibling;

    while (nextTemp != null) {

      if ((temp.degree != nextTemp.degree)
              || ((nextTemp.rightSibling != null)
              && (nextTemp.rightSibling.degree
              == temp.degree))) {
        prevTemp = temp;
        temp = nextTemp;
      } else {

        if (temp.key <= nextTemp.key) {
          temp.rightSibling = nextTemp.rightSibling;
          nextTemp.parent = temp;
          nextTemp.rightSibling = temp.leftMostChild;
          temp.leftMostChild = nextTemp;
          temp.degree++;
        } else {

          if (prevTemp == null) {
            Nodes = nextTemp;
          } else {
            prevTemp.rightSibling = nextTemp;
          }

          temp.parent = nextTemp;
          temp.rightSibling = nextTemp.leftMostChild;
          nextTemp.leftMostChild = temp;
          nextTemp.degree++;
          temp = nextTemp;
        }
      }
      nextTemp = temp.rightSibling;
    }
  }


  public int findMinimum() {
    return Nodes.findMinNode().key;
  }


  public void delete(int value) {

    if ((Nodes != null)
            && (Nodes.findANodeWithKey(value) != null)) {
      decreaseKeyValue(value, findMinimum() - 1);
      extractMin();
    }
  }


  public void decreaseKeyValue(int old_value,
                               int new_value) {
    BinomialHeapNode temp
            = Nodes.findANodeWithKey(old_value);
    if (temp == null)
      return;
    temp.key = new_value;
    BinomialHeapNode tempParent = temp.parent;

    while ((tempParent != null)
            && (temp.key < tempParent.key)) {
      int z = temp.key;
      temp.key = tempParent.key;
      tempParent.key = z;

      temp = tempParent;
      tempParent = tempParent.parent;
    }
  }


  public int extractMin() {
    if (Nodes == null)
      return -1;

    BinomialHeapNode temp = Nodes, prevTemp = null;
    BinomialHeapNode minNode = Nodes.findMinNode();

    while (temp.key != minNode.key) {
      prevTemp = temp;
      temp = temp.rightSibling;
    }

    if (prevTemp == null) {
      Nodes = temp.rightSibling;
    } else {
      prevTemp.rightSibling = temp.rightSibling;
    }

    temp = temp.leftMostChild;
    BinomialHeapNode fakeNode = temp;

    while (temp != null) {
      temp.parent = null;
      temp = temp.rightSibling;
    }

    if ((Nodes == null) && (fakeNode == null)) {
      size = 0;
    } else {
      if ((Nodes == null) && (fakeNode != null)) {
        Nodes = fakeNode.reverse(null);
        size = Nodes.getSize();
      } else {
        if ((Nodes != null) && (fakeNode == null)) {
          size = Nodes.getSize();
        } else {
          union(fakeNode.reverse(null));
          size = Nodes.getSize();
        }
      }
    }

    return minNode.key;
  }


  public void printHeap() {
    BinomialHeapNode curr = this.Nodes;
    while (curr != null) {
      System.out.println("B" + curr.degree);
      System.out.println("There are " + Math.pow(2, curr.degree) + " nodes in this binomial tree");
      System.out.println("The level order traversal of the tree is :");
      this.printTree(curr);
      curr = curr.rightSibling;
      System.out.println("\n");
    }
  }

  void printTree(BinomialHeapNode root) {
    if (root == null) {
      return;
    }
    Queue<BinomialHeapNode> q = new LinkedList<>();
    q.add(root);
    int currentLevel = 1;
    int nextLevel = 0;
    while (!q.isEmpty()) {
      BinomialHeapNode node = q.poll();
      currentLevel--;
      System.out.print(node.key + " ");

      if (node.leftMostChild != null) {
        BinomialHeapNode temp = node.leftMostChild;
        while (temp != null) {
          q.add(temp);
          temp = temp.rightSibling;
          nextLevel++;
        }
      }
      if (currentLevel == 0) {
        System.out.println("");
        currentLevel = nextLevel;
        nextLevel = 0;
      }
    }
  }

}
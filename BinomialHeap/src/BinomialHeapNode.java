//package src;

public class BinomialHeapNode {

  int key, degree;
  BinomialHeapNode parent;
  BinomialHeapNode rightSibling;
  BinomialHeapNode leftMostChild;

  public BinomialHeapNode(int k) {
    key = k;
    degree = 0;
    parent = null;
    rightSibling = null;
    leftMostChild = null;
  }

  public BinomialHeapNode reverse(BinomialHeapNode sibl) {
    BinomialHeapNode ret;
    if (rightSibling != null)
      ret = rightSibling.reverse(this);
    else
      ret = this;
    rightSibling = sibl;
    return ret;
  }


  public BinomialHeapNode findMinNode() {
    BinomialHeapNode x = this, y = this;
    int min = x.key;
    while (x != null) {
      if (x.key < min) {
        y = x;
        min = x.key;
      }
      x = x.rightSibling;
    }
    return y;
  }

  public BinomialHeapNode findANodeWithKey(int value) {
    BinomialHeapNode temp = this, node = null;
    while (temp != null) {
      if (temp.key == value) {
        node = temp;
        break;
      }
      if (temp.leftMostChild == null)
        temp = temp.rightSibling;
      else {
        node = temp.leftMostChild.findANodeWithKey(value);
        if (node == null)
          temp = temp.rightSibling;
        else
          break;
      }
    }
    return node;
  }


  public int getSize() {
    return (1 + ((leftMostChild == null) ? 0 : leftMostChild.getSize())
            + ((rightSibling == null) ? 0 : rightSibling.getSize()));
  }
}
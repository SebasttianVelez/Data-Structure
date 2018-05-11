#include <iostream>
#include <string>
#include <queue>
#include <cassert>

using namespace std;

template <typename T>
class BST {
private:
  class Node {
  private:
    T data_;
    Node* left_, *right_, *parent_;

  public:
    Node(T d) {
      data_ = d;
      left_ = NULL;
      right_ = NULL;
      parent_ = NULL;
    }
    /**
     * @brief Returns the data stored by the node.
     */
    T getData(void) { return data_; }
    /**
     * @brief Sets the data stored by the node to be @a d.
     */
    void setData(T d) { data_ = d; }
    /**
     * @brief Returns the left subtree of the node.
     */
    Node* getLeft(void) { return left_; }
    /**
     * @brief Returns the right subtree of the node.
     */
    Node* getRight(void) { return right_; }
    /**
     * @brief Returns the parent of the node.
     */
    Node* getParent(void) { return parent_; }
    /**
     * @brief Sets the left subtree of the node to be @a n.
     */
    void setLeft(Node* n) { left_ = n; }
    /**
     * @brief Sets the right subtree of the node to be @a n.
     */
    void setRight(Node* n) { right_ = n; }
    /**
     * @brief Sets the parent of the node to be @a n.
     */
    void setParent(Node* n) { parent_ = n; }
    /**
     * @brief Tests whether the node has a left subtree.
     */
    bool hasLeftChild(void) { return left_ != NULL; }
    /**
     * @brief Tests whether the node has a right subtree.
     */
    bool hasRightChild(void) { return right_ != NULL; }
    /**
     * @brief Tests whether the node is a leaf
     */
    bool isLeaf(void) { return !hasLeftChild() && !hasRightChild(); }
  };

private:
  /// Pointer to the root of the tree
  Node* root_;
  /// Size of the tree
  int size_;

public:
  /**
   * @brief Constructs an empty BST.
   *
   * Time complexity: O(?)
   */
  BST(void) {
    root_ = NULL;
    size_ = 0;
  }
  /**
   * @brief Tests whether the tree is empty.
   *
   * Time complexity: O(?)
   */
  bool isEmpty(void) const { return root_ == NULL; }
  /**
   * @brief Inserts a node with data @a d
   *
   * Time complexity: O(?)
   */
  void insert(T d) {
    if (isEmpty()) {
      root_ = new Node(d);
      size_++;
    } else {
      insert(d, root_);
    }
  }

private:
  /**
   * @brief Helper method for insert.
   *
   * Time complexity: O(?)
   */
  void insert(T d, Node* n) {
    if (n->getData() == d) return;
    if (d < n->getData()) {
      if (!n->hasLeftChild()) {
        Node* x = new Node(d);
        n->setLeft(x);
        x->setParent(n);
        size_++;
      } else {
        insert(d, n->getLeft());
      }
    } else { // d > n->getData()
      if (!n->hasRightChild()) {
        Node* x = new Node(d);
        n->setRight(x);
        x->setParent(n);
        size_++;
      } else {
        insert(d, n->getRight());
      }
    }
  }

public:
  /**
   * @brief Prints the elements of the tree using an in-order traversal
   *
   * Time complexity: O(?)
   */
  void printInorder(void) {
    if (isEmpty()) return;
    printInorder(root_);
    cout << endl;
  }

private:
  /**
   * @brief Helper method to print the elements of the tree using an in-order
   * traversal
   *
   * Time complexity: O(?)
   */
  void printInorder(Node* n) {
    if (n->hasLeftChild()) printInorder(n->getLeft());
    cout << n->getData() << " ";
    if (n->hasRightChild()) printInorder(n->getRight());
  }

public:
  /**
   * @brief Prints the elements of the tree by levels
   *
   * Time complexity: O(?)
   */
  void printLevelOrder(void) {
    // do it!
  }

public:
  /**
   * @brief Returns the number of elements int the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  int size(void) { return size_; }

public:
  /**
   * @brief Returns the number of leaves in the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  int countLeaves(void) {
    if (isEmpty()) return 0;
    return countLeaves(root_);
  }

private:
  /**
   * @brief Helper method to count the number of leaves in the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  int countLeaves(Node* n) {
    // do it
    return 0;
  }

public:
  /**
   * @brief Finds the minimum element in the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  T findMin(void) {
    assert(!isEmpty());
    return findMin(root_)->getData();
  }

private:
  /**
   * @brief Helper method to find the minimum element in the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  Node* findMin(Node* n) {
    if (n->hasLeftChild()) return findMin(n->getLeft());
    return n;
  }

public:
  /**
   * @brief Finds the maximum element in the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  T findMax(void) {
    assert(!isEmpty());
    return findMax(root_)->getData();
  }

private:
  /**
   * @brief Helper method to find the minimum element in the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  Node* findMax(Node* n) {
    if (n->hasRightChild()) return findMax(n->getRight());
    return n;
  }

public:
  /**
   * @brief Tests whether a node with key @a d is in the tree.
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  bool find(T d) { return find(d, root_) != NULL; }

private:
  /**
   * @brief Helper function that finds a node with key @a d in the tree.
   *
   * Returns a pointer to the node if found or NULL if a node with that
   * key is not in the tree.
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  Node* find(T d, Node* n) {
    if (n == NULL || n->getData() == d) return n;
    if (d < n->getData())
      return find(d, n->getLeft());
    else
      return find(d, n->getRight());
  }

public:
  /**
   * @brief Returns the successor of key @a d in the tree.
   *
   * The successor of @a d is the smallest key greater than @a d in the tree.
   * This method returns a pair <b,s> where @a b is a boolean indicating if the
   * successor was found and @a s is its actual value.
   */
  pair<bool, T> successor(T d) {
    if (isEmpty()) return make_pair(false, T());
    Node* x = find(d, root_);
    if (x == NULL) return make_pair(false, T());
    Node* y = successor(x);
    if (y == NULL) return make_pair(false, T());
    return make_pair(true, y->getData());
  }

  /**
   * @brief Returns the successor of a node with value @a x in the tree.
   *
   * The successor of node @a x is the node with the smallest key greater than
   * @a x.
   */
  Node* successor(Node* x) {
    // Do it
  }

public:
  /**
   * @brief Removes the node with value @a d from the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  void remove(T d) {
    if (isEmpty()) return;
    Node* z = find(d, root_);
    if (z == NULL) return;
    remove(z);
  }

private:
  /**
   * @brief Removes the node @a z from the tree
   */
  void remove(Node* z) {
    // Let's do it!
  }

  /**
   * @brief Tests whether keys @a n and @a m are stored on cousin nodes.
   *
   */
  bool cousinNodes(T n, T m) {
    // Let's do it
    return false;
  }

public:
  /**
   * @brief Prints the tree in DOT format.
   *
   * The following site can be used to visualize the result. Just copy and paste
   * the generated code to visualize the tree.
   *
   * http://sandbox.kidstrythisathome.com/erdos/
   *
   * In the text box with title "DOT code for the graph" put what is printed
   * between the dashed lines (without icluding them!). In the graphviz engine
   * select "dot" and then push the button "Make me a graph". After these steps
   * you will see the BST on the right canvas.
   */
  void printDOT(bool showParent = false, bool useInvis = true) {
    if (isEmpty()) return;
    string dashedLine(30, '-');
    cout << dashedLine << endl;
    cout << "digraph BST {" << endl << "\tnode [fontname=\"Arial\"];" << endl;
    if (root_->isLeaf())
      cout << "\t" << root_->getData() << endl;
    else {
      int nullNodes = 0;
      printDOT(root_, nullNodes, showParent, useInvis);
    }
    cout << "}" << endl;
    cout << dashedLine << endl;
  }

private:
  /**
   * @brief Helper method to print the tree in DOT format.
   */
  void printDOT(Node* n, int& nullNodes, bool showParent = false,
                bool useInvis = true) {
    if (n->hasLeftChild()) {
      cout << "\t" << n->getData() << " -> " << n->getLeft()->getData() << ";"
           << endl;
      if (showParent)
        cout << "\t" << n->getLeft()->getData() << " -> "
             << n->getLeft()->getParent()->getData() << "[color=\"red\"];"
             << endl;

      printDOT(n->getLeft(), nullNodes, showParent, useInvis);
    } else {
      printNULL(n->getData(), nullNodes, useInvis);
      nullNodes++;
    }
    if (n->hasRightChild()) {
      cout << "\t" << n->getData() << " -> " << n->getRight()->getData() << ";"
           << endl;
      if (showParent)
        cout << "\t" << n->getRight()->getData() << " -> "
             << n->getRight()->getParent()->getData() << "[color=\"red\"];"
             << endl;

      printDOT(n->getRight(), nullNodes, showParent, useInvis);
    } else {
      printNULL(n->getData(), nullNodes, useInvis);
      nullNodes++;
    }
  }
  /**
   * @brief Helper method to print the tree in DOT format.
   *
   * This method only prints null nodes.
   */
  void printNULL(T d, int nullNode, bool useInvis) {
    if (useInvis) {
      cout << "\tnull" << nullNode << " [shape=point,style=invis];" << endl;
      cout << "\t" << d << "-> \tnull" << nullNode << "[style=invis];" << endl;
    } else {
      cout << "\tnull" << nullNode << " [shape=point];" << endl;
      cout << "\t" << d << "-> \tnull" << nullNode << ";" << endl;
    }
  }
};

int main(void) {
  cout << "BST examples!" << endl;
  BST<int> cormen122;
  cormen122.insert(15);
  cormen122.insert(6);
  cormen122.insert(18);
  cormen122.insert(3);
  cormen122.insert(7);
  cormen122.insert(17);
  cormen122.insert(20);
  cormen122.insert(2);
  cormen122.insert(4);
  cormen122.insert(13);
  cormen122.insert(9);

  cormen122.printDOT();
  return 0;
}

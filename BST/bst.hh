#ifndef __BST_HH__
#define __BST_HH__

#include <algorithm>
#include <cassert>
#include <iostream>
#include <queue>
#include <utility>

using std::cout;
using std::endl;
using std::queue;
using std::pair;
using std::make_pair;
using std::max;

/**
 * Implementation of the Binary Search Tree data structure.
 */
template <typename T>

class BST {
private:
  /* Definition for every node in the tree */
  class Node {
  private:
    T data_;
    Node *left_;
    Node *right_;

  public:
    /**
     * Constructs a node initializing its data field with d.
     */
    Node(T d) {
      data_ = d;
      left_ = nullptr;
      right_ = nullptr;
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
    Node *getLeft(void) { return left_; }
    /**
     * @brief Returns the right subtree of the node.
     */
    Node *getRight(void) { return right_; }
    /**
     * @brief Sets the left subtree of the node to be @a n.
     */
    void setLeft(Node *n) { left_ = n; }
    /**
     * @brief Sets the right subtree of the node to be @a n.
     */
    void setRight(Node *n) { right_ = n; }
    /**
     * @brief Tests whether the node has a left subtree.
     */
    bool hasLeftChild(void) { return left_ != nullptr; }
    /**
     * @brief Tests whether the node has a right subtree.
     */
    bool hasRightChild(void) { return right_ != nullptr; }
    /**
     * @brief Tests whether the node is a leaf
     */
    bool isLeaf(void) { return !hasLeftChild() && !hasRightChild(); }
  };

private:
  /// Pointer to the root of the tree
  Node *root_;
  /// Size of the tree
  int size_;

public:
  /**
   * @brief Constructs an empty BST.
   *
   * Time complexity: O(1)
   */
  BST(void) {
    root_ = nullptr;
    size_ = 0;
  }

  /**
   * @brief Deallocates the BST
   */
  ~BST(void) { clear(); }
  /**
   * Removes all the elements of the tree.
   */
  void clear(void) {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
  }

private:
  /**
   * Removes all the elements of the tree.
   */
  void clear(Node *n) {
    if (n->hasLeftChild())
      clear(n->getLeft());
    if (n->hasRightChild())
      clear(n->getRight());
    delete n;
  }

public:
  /**
   * @brief Tests whether the tree is empty.
   *
   * Time complexity: O(1)
   */
  bool isEmpty(void) const { return root_ == nullptr; }

public:
  /**
   * @brief Inserts a node with data @a d
   *
   * Time complexity: O(h), with h being the height of the tree.
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
   * Time complexity: O(h), with h being the height of the tree.
   */
  void insert(T d, Node *n) {
    if (n->getData() == d)
      return;
    if (d < n->getData()) {
      if (!n->hasLeftChild()) {
        Node *x = new Node(d);
        n->setLeft(x);
        size_++;
      } else {
        insert(d, n->getLeft());
      }
    } else { // d > n->getData()
      if (!n->hasRightChild()) {
        Node *x = new Node(d);
        n->setRight(x);
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
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  void printInorder(void) {
    if (isEmpty())
      return;
    printInorder(root_);
    cout << endl;
  }

private:
  /**
   * @brief Helper method to print the elements of the tree using an in-order
   * traversal
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  void printInorder(Node *n) {
    if (n->hasLeftChild())
      printInorder(n->getLeft());
    cout << n->getData() << " ";
    if (n->hasRightChild())
      printInorder(n->getRight());
  }

public:
  /**
   * Prints the contents of the tree by levels.
   */
  void printLevelOrder(void) {
    if (isEmpty())
      return;
    queue<Node *> q;
    q.push(root_);
    while (!q.empty()) {
      Node *e = q.front();
      q.pop();
      cout << e->getData() << " ";
      if (e->hasLeftChild())
        q.push(e->getLeft());
      if (e->hasRightChild())
        q.push(e->getRight());
    }
    cout << endl;
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
  Node *findMin(Node *n) {
    if (n->hasLeftChild())
      return findMin(n->getLeft());
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
  Node *findMax(Node *n) {
    if (n->hasRightChild())
      return findMax(n->getRight());
    return n;
  }

public:
  /**
   * @brief Tests whether a node with key @a d is in the tree.
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  bool find(T d) {
    assert(!isEmpty());

    return find(d, root_) != nullptr;
  }

private:
  /**
   * @brief Helper function that finds a node with key @a d in the tree.
   *
   * Returns a pointer to the node if found or nullptr if a node with that
   * key is not in the tree.
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  Node *find(T d, Node *n) {
    if (n == nullptr || n->getData() == d)
      return n;
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
    if (isEmpty())
      return make_pair(false, T());
    Node *succ = successorHelper(d);
    if (succ == nullptr)
      return make_pair(false, T());
    return make_pair(true, succ->getData());
  }

  /**
   * @brief Returns the successor of a node with value @a x in the tree.
   *
   * The successor of node @a x is the node with the smallest key greater than
   * @a x.
   */
  Node *successorHelper(T d) {
    Node *current = find(d, root_);
    if (current == nullptr)
      // d does not exists in the tree and hence has no successor
      return nullptr;
    if (current->hasRightChild())
      // Case 1: the node containing d has a right child and hence the minimum
      // of the right subtree is the successor of d.
      return findMin(current->getRight());
    else {
      // Case 2: current has no right child so the successor of d is "up in the
      // tree". It is actually the first node from current to the root for which
      // current is in a right subtree.
      Node *successor = nullptr;
      Node *ancestor = root_;
      while (ancestor != current) {
        if (current->getData() < ancestor->getData()) {
          successor = ancestor;
          ancestor = ancestor->getLeft();
        } else
          ancestor = ancestor->getRight();
      }
      return successor;
    }
  }

public:
  /**
   * @brief Removes the node with value @a d from the tree
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  void remove(T d) {
    if (isEmpty())
      return;
    root_ = remove(d, root_);
  }

private:
  /**
   * @brief Helper method to remove the node with value @a d from the tree.
   *
   * This method returns a pointer to the new tree because it can be changed.
   * you can think of the parameter @a n as the root node of the current subtree
   * and about the returned pointer as the new subtree that should replace @a n.
   *
   * Time complexity: O(h), with h being the height of the tree.
   */
  Node *remove(T d, Node *n) {
    if (d < n->getData()) {
      Node *result = remove(d, n->getLeft());
      n->setLeft(result);
      return n;
    } else if (d > n->getData()) {
      Node *result = remove(d, n->getRight());
      n->setRight(result);
      return n;
    } else { // n->getData() == d, hence we have to delete node n.
      if (n->isLeaf()) {
        delete n;
        size_--;
        return nullptr;
      } else if (!n->hasLeftChild()) {
        // n is a node with only right child
        Node *tmp = n->getRight();
        delete n;
        size_--;
        return tmp;
      } else if (!n->hasRightChild()) {
        // n is a node with only left child
        Node *tmp = n->getLeft();
        delete n;
        size_--;
        return tmp;
      } else {
        // n has two children
        Node *tmp = findMin(n->getRight());
        n->setData(tmp->getData());
        Node *result = remove(tmp->getData(), n->getRight());
        n->setRight(result);
        return n;
      }
    }
  }
  /*
      Other operations that are more interesting from the academic perspective
      than from the data structures view point.
   */
public:
  /**
   * @brief Returns the number of leaves in the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  int countLeaves(void) {
    if (isEmpty())
      return 0;
    return countLeaves(root_);
  }

private:
  /**
   * @brief Helper method to count the number of leaves in the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  int countLeaves(Node *n) {
    if (n->isLeaf())
      return 1;
    int c = 0;
    if (n->hasLeftChild())
      c = c + countLeaves(n->getLeft());
    if (n->hasRightChild())
      c = c + countLeaves(n->getRight());
    return c;
  }

public:
  size_t height(void) {
    if (isEmpty())
      return 0;
    return height(root_);
  }

private:
  size_t height(Node *n) {
    size_t leftHeight = 0;
    if (n->hasLeftChild())
      leftHeight = height(n->getLeft());
    size_t rightHeight = 0;
    if (n->hasRightChild())
      rightHeight = height(n->getRight());
    return max(leftHeight, rightHeight) + 1;
  }
};

#endif

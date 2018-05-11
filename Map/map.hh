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
 * Implementation of the set data structure.
 */
template <typename D>
template <typename T>

class Map {
private:
  /* Definition for every node in the tree */
  class Node {
  private:
    T key_;
    T value_;
    Node *left_;
    Node *right_;

  public:
    /**
     * Constructs a node initializing its data field with d.
     */
    Node(T d, D v) {
      key_ = d;
      value_ = v;
      left_ = nullptr;
      right_ = nullptr;
    }

    /**
     * @brief Returns the data stored by the node.
     */
    T getData(void) { return key_; }
    T getValue(D v) { return value_; }

    /**
     * @brief Maps the data stored by the node to be @a d.
     */
    void setData(T d) { key_ = d; }
    void setValue(D v) { value_ = v; }
    /**
     * @brief Returns the left subtree of the node.
     */
    Node *getLeft(void) { return left_; }
    /**
     * @brief Returns the right subtree of the node.
     */
    Node *getRight(void) { return right_; }
    /**
     * @brief Maps the left subtree of the node to be @a n.
     */
    void setLeft(Node *n) { left_ = n; }
    /**
     * @brief Maps the right subtree of the node to be @a n.
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
  unsigned int size_;

public:
  /**
   * @brief Constructs an empty set.
   *
   * Time complexity: O(1)
   */
  Map() {
    root_ = nullptr;
    size_ = 0;
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
   * @brief Inserts the element @a d
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
  void print(void) {
    if (isEmpty()) {
      cout << "{}" << endl;
    } else {
      cout << "{ ";
      print(root_);
      cout << "}" << endl;
    }
  }

private:
  /**
   * @brief Helper method to print the elements of the tree using an in-order
   * traversal
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  void print(Node *n) {
    if (n->hasLeftChild())
      print(n->getLeft());
    cout << n->getData() << " ";
    if (n->hasRightChild())
      print(n->getRight());
  }

  void copy(Node *n, Map<T> &dest) {
    if (n->hasLeftChild())
      copy(n->getLeft(), dest);
    dest.insert(n->getData());
    if (n->hasRightChild())
      copy(n->getRight(), dest);
  }

public:
  Map<T> Union(Map<T> &x) {
    Map<T> result;
    copy(root_, result);
    copy(x.root_, result);
    return result;
  }

private:
  void copyIfMember(Node *n, Map<T> &c, Map<T> &dest) {
    if (n->hasLeftChild())
      copyIfMember(n->getLeft(), c, dest);
    if (c.member(n->getData())) {
      dest.insert(n->getData());
    }
    if (n->hasRightChild())
      copyIfMember(n->getRight(), c, dest);
  }

public:
  Map<T> Intersect(Map<T> &x) {
    Map<T> result;
    copyIfMember(root_, x, result);
    return result;
  }

public:
  /**
   * @brief Returns the number of elements int the tree
   *
   * Time complexity: O(n) with n being the number of elements in the tree.
   */
  unsigned int size() { return size_; }

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
  bool member(T d) {
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
};

#endif

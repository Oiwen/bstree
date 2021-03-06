#pragma once
#include <iostream>
#include <ostream>
#include <memory>
#include <queue>
#include <utility>

#include "node.hpp"

template <class Comparable>
class BST
{
public:
  BST() {}

  BST(const BST &other) = delete;

  BST(BST &&other)
      : m_root(std::move(other.m_root)) {}

  ~BST() {}

  BST &operator=(const BST &other) = delete;

  BST &operator=(BST &&other)
  {
    m_root = std::move(other.m_root);
    return *this;
  }

  std::unique_ptr<Comparable> findMin();
  std::unique_ptr<Comparable> findMax();

  bool contains(const Comparable &x);
  bool isEmpty() const;

  void insert(const Comparable &x);
  void insert(Comparable &&x);
  void remove(const Comparable &x);

  void print(std::ostream &out = std::cout);

  void preorder() const;
  void inorder() const;
  void postorder() const;
  void levelorder_iterative() const;
private:
  std::unique_ptr<Node<Comparable>> m_root{nullptr};

  void insert(const Comparable &x, std::unique_ptr<Node<Comparable>> &node);
  void insert(Comparable &&x, std::unique_ptr<Node<Comparable>> &node);
  void remove(const Comparable &x, std::unique_ptr<Node<Comparable>> &node);
  std::unique_ptr<Comparable> findMin(std::unique_ptr<Node<Comparable>> &node);
  std::unique_ptr<Comparable> findMax(std::unique_ptr<Node<Comparable>> &node);
  bool contains(const Comparable &x, std::unique_ptr<Node<Comparable>> &node);
  void print(std::unique_ptr<Node<Comparable>> &node, std::ostream &out);

  void preorder(const std::unique_ptr<Node<Comparable>> &node) const;
  void inorder(const std::unique_ptr<Node<Comparable>> &node) const;
  void postorder(const std::unique_ptr<Node<Comparable>> &node) const;
  void levelorder_iterative(const std::unique_ptr<Node<Comparable>> &node) const;

  void visit(const Comparable& x) const;
};

template <class Comparable>
bool BST<Comparable>::isEmpty() const
{
  if (m_root == nullptr)
  {
    return true;
  }

  return false;
}

template <class Comparable>
void BST<Comparable>::print(std::ostream &out)
{
  if (isEmpty())
  {
    return;
  }

  print(m_root, out);
  out << std::endl;
}

template <class Comparable>
void BST<Comparable>::print(std::unique_ptr<Node<Comparable>> &node, std::ostream &out)
{
  if (node == nullptr)
  {
    return;
  }

  out << node->element << ' ';
  print(node->left, out);
  print(node->right, out);
}

template <class Comparable>
std::unique_ptr<Comparable>
BST<Comparable>::findMin()
{
  if (isEmpty())
  {
    return nullptr;
  }

  return findMin(m_root);
}

template <class Comparable>
std::unique_ptr<Comparable>
BST<Comparable>::findMin(std::unique_ptr<Node<Comparable>> &node)
{
  if (node->left == nullptr)
  {
    return std::make_unique<Comparable>(node->element);
  }

  return findMin(node->left);
}

template <class Comparable>
std::unique_ptr<Comparable>
BST<Comparable>::findMax()
{
  if (isEmpty())
  {
    return nullptr;
  }

  return findMax(m_root);
}

template <class Comparable>
std::unique_ptr<Comparable>
BST<Comparable>::findMax(std::unique_ptr<Node<Comparable>> &node)
{
  if (node->left == nullptr)
  {
    return std::make_unique<Comparable>(node->element);
  }

  return findMax(node->left);
}

template <class Comparable>
bool BST<Comparable>::contains(const Comparable &x)
{
  return BST<Comparable>::contains(x, m_root);
}

template <class Comparable>
bool BST<Comparable>::contains(const Comparable &x,
                               std::unique_ptr<Node<Comparable>> &node)
{
    static int depthOfRecursion = 0;

    depthOfRecursion++;
  if (node == nullptr)
  {
    return false;
  }
  else if (x < node->element)
  {
    return BST<Comparable>::contains(x, node->left);
  }
  else if (x > node->element)
  {
    return BST<Comparable>::contains(x, node->right);
  }
  else
  {
      std::cout << "Depth of Recursion is: " << depthOfRecursion << "\n";
    return true;
  }
}

template <class Comparable>
void BST<Comparable>::insert(const Comparable &x)
{
  BST<Comparable>::insert(x, m_root);
}

template <class Comparable>
void BST<Comparable>::insert(const Comparable &x,
                             std::unique_ptr<Node<Comparable>> &node)
{
  if (node == nullptr)
  {
    node = std::make_unique<Node<Comparable>>(x, nullptr, nullptr);
    //node = std::move(Node<Comparable>(x, nullptr, nullptr));
  }
  else if (x < node->element)
  {
    insert(x, node->left);
  }
  else
  {
    insert(x, node->right);
  }
}

template <class Comparable>
void BST<Comparable>::insert(Comparable &&x)
{
  BST<Comparable>::insert(std::move(x), m_root);
}

template <class Comparable>
void BST<Comparable>::insert(Comparable &&x,
                             std::unique_ptr<Node<Comparable>> &node)
{
  if (node == nullptr)
  {
    node = std::make_unique(std::move(x), nullptr, nullptr);
    //node = std::move(Node<Comparable>(std::move(x), nullptr, nullptr));
  }
  else if (x < node->element)
  {
    insert(std::move(x), node->left);
  }
  else
  {
    insert(std::move(x), node->right);
  }
}

template <class Comparable>
void BST<Comparable>::remove(const Comparable &x)
{
  remove(x, m_root);
}

template <class Comparable>
void BST<Comparable>::remove(const Comparable &x, std::unique_ptr<Node<Comparable>> &node)
{
  if (isEmpty())
  {
    return;
  }

  if (x < node->element)
  {
    remove(x, node->left);
  }
  else if (x > node->element)
  {
    remove(x, node->right);
  }
  else if ((node->left != nullptr) && (node->right != nullptr))
  {
    node->element = *findMin(node->right);
    remove(node->element, node->right);
  }
  else
  {
    node = (node->left != nullptr) ? std::move(node->left) : std::move(node->right);
  }
}


template <class Comparable>
void BST<Comparable>::preorder() const
{
  if(m_root == nullptr) 
  {
    return;
  }

  preorder(m_root);
}

template <class Comparable>
void BST<Comparable>::inorder() const
{
  if(m_root == nullptr) 
  {
    return;
  }

  inorder(m_root); 
}

template <class Comparable>
void BST<Comparable>::postorder() const
{
  if(m_root == nullptr) 
  {
    return;
  }

  postorder(m_root);
}

template <class Comparable>
void BST<Comparable>::preorder(const std::unique_ptr<Node<Comparable>> &node) const
{
  if(node == nullptr) 
  {
    return;
  }

  visit(node->element);
  preorder(node->left);
  preorder(node->right); 
}

template <class Comparable>
void BST<Comparable>::inorder(const std::unique_ptr<Node<Comparable>> &node) const
{
  if(node == nullptr) 
  {
    return;
  }

  inorder(node->left);
  visit(node->element);
  inorder(node->right); 
}

template <class Comparable>
void BST<Comparable>::postorder(const std::unique_ptr<Node<Comparable>> &node) const
{
  if(node == nullptr) 
  {
    return;
  }

  postorder(node->left);
  postorder(node->right); 
  visit(node->element);
}

template <class Comparable>
void BST<Comparable>::levelorder_iterative() const 
{
  if(m_root == nullptr)
  {
    return;
  }

  levelorder_iterative(m_root);
}

template <class Comparable>
void BST<Comparable>::levelorder_iterative(const std::unique_ptr<Node<Comparable>> &node) const
{
  std::queue<const Node<Comparable>*> q; 
  const auto* pNode = node.get();
  q.push(pNode);

  while(!q.empty()) {
    pNode = q.front();
    q.pop();
    visit(pNode->element);

    if(pNode->left != nullptr) {
      q.push(pNode->left.get());
    }

    if(pNode->right != nullptr) {
      q.push(pNode->right.get());
    }
  }
}

template <class Comparable>
void BST<Comparable>::visit(const Comparable& v) const
{
  std::cout << v << std::endl;
}

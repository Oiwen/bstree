#pragma once
#include <iostream>
#include <ostream>
#include <memory>

template <class Comparable>
class BST
{
  struct Node
  {
    Comparable element;
    std::unique_ptr<Node> left{nullptr};
    std::unique_ptr<Node> right{nullptr};

    Node(const Comparable &element_,
         std::unique_ptr<Node> left_,
         std::unique_ptr<Node> right_)
        : element(element_),
          left(std::move(left_)),
          right(std::move(right_)) {}

    Node(Comparable &&element_,
         std::unique_ptr<Node> left_,
         std::unique_ptr<Node> right_)
        : element(element_),
          left(std::move(left_)),
          right(std::move(right_)) {}
  };

public:
  BST() {}

  // I'm don't know what to do with this shit.
  BST(const BST &other) = delete;

  BST(BST &&other)
      : m_root(std::move(other.m_root)) {}

  ~BST() {}

  std::unique_ptr<Comparable> findMin();
  std::unique_ptr<Comparable> findMax();

  bool contains(const Comparable &x);
  bool isEmpty() const;

  void insert(const Comparable &x);
  void insert(Comparable &&x);
  void remove(const Comparable &x);

  void print(std::ostream &out = std::cout);

  // I'm don't know what to do with this shit.
  BST &operator=(const BST &other) = delete;

  BST &operator=(BST &&other)
  {
    m_root = std::move(other.m_root);
    return *this;
  }

private:
  std::unique_ptr<Node> m_root{nullptr};

  void insert(const Comparable &x, std::unique_ptr<Node> &node);
  void insert(Comparable &&x, std::unique_ptr<Node> &node);
  void remove(const Comparable &x, std::unique_ptr<Node> &node);
  std::unique_ptr<Comparable> findMin(std::unique_ptr<Node> &node);
  std::unique_ptr<Comparable> findMax(std::unique_ptr<Node> &node);
  bool contains(const Comparable &x, std::unique_ptr<Node> &node);
  void print(std::unique_ptr<Node> &node, std::ostream &out);
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
void BST<Comparable>::print(std::unique_ptr<Node> &node, std::ostream &out)
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
BST<Comparable>::findMin(std::unique_ptr<Node> &node)
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
BST<Comparable>::findMax(std::unique_ptr<Node> &node)
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
                               std::unique_ptr<Node> &node)
{
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
                             std::unique_ptr<Node> &node)
{
  if (node == nullptr)
  {
    node = std::make_unique<Node>(x, nullptr, nullptr);
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
                             std::unique_ptr<Node> &node)
{
  if (node == nullptr)
  {
    node = std::make_unique<Node>(std::move(x), nullptr, nullptr);
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
void BST<Comparable>::remove(const Comparable &x, std::unique_ptr<Node> &node)
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

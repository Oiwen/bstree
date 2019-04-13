#pragma once
#include <iostream>
#include <ostream>
#include <memory>

template <class Comparable>
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

  ~Node()
  {
    left = nullptr;
    right = nullptr;
  }
};


#pragma once

#include "bag.hpp"

class tree_bag : virtual public bag {
protected:
  struct node {
    node *l;
    node *r;
    int value;
  };
  node *tree;

public:
  tree_bag();
  tree_bag(const tree_bag &);
  tree_bag &operator=(const tree_bag &src);
  ~tree_bag();

  node *extract_tree();
  void set_tree(node *);

  virtual void insert(int);
  virtual void insert(int *array, int size);
  virtual void print() const;
  virtual void clear();
  int* export_to() const;

protected:
  int count_nodes(node *) const;

private:
  static void destroy_tree(node *);
  static void print_node(node *);
  static node *copy_node(node *);
  void nodesToArr(node* cur, int * array, int & count) const;
};

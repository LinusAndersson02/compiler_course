#ifndef NODE_H
#define NODE_H

#include <fstream>
#include <iostream>
#include <list>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

using namespace std;

class Node {
public:
  int id, lineno;
  string type, value;
  list<Node *> children;

  Node(string t, string v, int l) : type(t), value(v), lineno(l) {}

  Node() {
    type = "uninitialised";
    value = "uninitialised";
  } // Bison needs this.

  // ----- NEW: indexed child access (O(n) because children is a std::list) -----
  Node *child(int idx) {
    if (idx < 0)
      return nullptr;
    auto it = children.begin();
    for (int i = 0; i < idx && it != children.end(); ++i)
      ++it;
    if (it == children.end())
      return nullptr;
    return *it;
  }

  const Node *child(int idx) const {
    if (idx < 0)
      return nullptr;
    auto it = children.begin();
    for (int i = 0; i < idx && it != children.end(); ++i)
      ++it;
    if (it == children.end())
      return nullptr;
    return *it;
  }

  void print_tree(int depth = 0) {
    for (int i = 0; i < depth; i++)
      cout << "  ";
    cout << type << ":" << value << endl;
    for (auto i = children.begin(); i != children.end(); i++)
      (*i)->print_tree(depth + 1);
  }

  void generate_tree() {
    std::ofstream outStream;
    char *filename = (char *)"tree.dot";
    outStream.open(filename);

    int count = 0;
    outStream << "digraph {" << std::endl;
    generate_tree_content(count, &outStream);
    outStream << "}" << std::endl;
    outStream.close();

    printf("\nBuilt a parse-tree at %s. Use 'make tree' to generate the pdf version.\n",
           filename);
  }

  void generate_tree_content(int &count, ofstream *outStream) {
    id = count++;
    *outStream << "n" << id << " [label=\"" << type << ":" << value << "\"];" << endl;

    for (auto i = children.begin(); i != children.end(); i++) {
      (*i)->generate_tree_content(count, outStream);
      *outStream << "n" << id << " -> n" << (*i)->id << endl;
    }
  }
};

#endif

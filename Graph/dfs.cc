#include <iostream>
#include "graph.hh"

/**
 * @brief Definition of a particular node in the graph.
 */
class Node {
private:
  string id_;

public:
  Node(void) {}
  Node(string id) { id_ = id; }
  string getId(void) const { return id_; }
  void setId(string id) { id_ = id; }
};

/**
 * @brief Definition of a particular edge in the graph.
 */
class Edge {
private:
  Node* start_;
  Node* end_;
  int weight_;

public:
  Edge(void) { weight_ = 0; }

  void setStart(Node* s) { start_ = s; }
  void setEnd(Node* e) { end_ = e; }

  Node* getStart(void) const { return start_; }
  Node* getEnd(void) const { return end_; }

  void setWeight(int w) { weight_ = w; }
  int getWeight(void) const { return weight_; }
};

Graph<Node, Edge>* dfsGraph(void) {
  Graph<Node, Edge>* g = new Graph<Node, Edge>();
  g->addNode("u");
  g->addNode("v");
  g->addNode("w");
  g->addNode("x");
  g->addNode("y");
  g->addNode("z");

  g->addEdge("u", "v");
  g->addEdge("u", "x");
  g->addEdge("v", "y");
  g->addEdge("y", "x");
  g->addEdge("x", "v");

  g->addEdge("w", "y");
  g->addEdge("w", "z");
  g->addEdge("z", "z");

  return g;
}

int main(void) {
  Graph<Node, Edge>* g = dfsGraph();
  // printDOT(cout, *g);

  unordered_map<Node*, size_t> discovered;
  unordered_map<Node*, size_t> finished;
  unordered_map<Node*, Node*> predecessor;

  dfs<Node, Edge>(g, discovered, finished, predecessor);

  // Output the order in which the nodes were discovered (increasing)
  map<size_t, Node*> d;
  for (pair<Node*, size_t> p : discovered) d[p.second] = p.first;
  for (pair<size_t, Node*> v : d) cout << v.second->getId() << " ";
  cout << endl;
  cout << "Finished DFS" << endl;
}

#ifndef __GRAPH_HH__
#define __GRAPH_HH__

#include <cassert>
#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <stack>
#include <queue>
#include <map>

using namespace std;

template <typename Node, typename Edge>
class Graph {
public:
  typedef unordered_set<Node*> NodeSet;
  typedef unordered_set<Edge*> EdgeSet;
  typedef unordered_map<Node*, list<Edge*>> OutEdgeSet;

  typedef list<Node*> AdjacencyList;

private:
  typedef unordered_map<Node*, AdjacencyList> AdjList;
  typedef unordered_map<string, Node*> NodeInfo;

private:
  NodeSet nodes_;
  EdgeSet edges_;
  AdjList adj_;
  NodeInfo nodeInfo_;
  OutEdgeSet outEdges_;

public:
  bool hasNodeWithId(string id) { return nodeInfo_.count(id) > 0; }

  Node* getNodeWithId(string id) {
    assert(hasNodeWithId(id));
    return nodeInfo_[id];
  }

public:
  /**
   * @brief Creates an empty graph.
   */
  Graph(void) {}

  Node* addNode(string id) {
    Node* n = new Node();
    n->setId(id);
    return addNode(n);
  }

  Node* addNode(Node* n) {
    // We cannot accpet more than one with the same identifier.
    assert(!hasNodeWithId(n->getId()));
    // Register the node by adding it to adj_ with an empty list.
    list<Node*> emptyList;
    adj_.insert(make_pair(n, emptyList));
    // Add the node to the set of nodes
    nodes_.insert(n);
    // Insert the node information
    nodeInfo_.insert(make_pair(n->getId(), n));
    return n;
  }

  Edge* addUndirectedEdge(string s, string e, int weight = 0) {
    Edge* edge = addEdge(s, e, weight);
    edge = addEdge(e, s, weight);
    return edge;
  }

  Edge* addEdge(string s, string e, int weight) {
    Edge* edge = addEdge(s, e);
    edge->setWeight(weight);
    return edge;
  }

  Edge* addEdge(string s, string e) {
    Node* st = getNodeWithId(s);
    Node* en = getNodeWithId(e);
    return addEdge(st, en);
  }

  Edge* addEdge(Node* s, Node* e) {
    Edge* edge = new Edge();
    // Keep the information in the edge about the start and end nodes.
    edge->setStart(s);
    edge->setEnd(e);
    return addEdge(edge);
  }

  Edge* addEdge(Edge* e) {
    // Register the edge in the adjacency list of s.
    adj_[e->getStart()].push_back(e->getEnd());
    outEdges_[e->getStart()].push_back(e);
    edges_.insert(e);
    return e;
  }

  size_t numNodes(void) const { return adj_.size(); }
  size_t numEdges(void) const { return edges_.size(); }

  NodeSet getNodes(void) { return nodes_; }
  EdgeSet getEdges(void) { return edges_; }

  AdjacencyList getAdjacentTo(Node* n) { return adj_[n]; }
  list<Edge*> getEdgesFrom(Node* n) { return outEdges_[n]; }

  AdjacencyList getAdjacentTo(string id) {
    Node* n = getNodeWithId(id);
    return getAdjacentTo(n);
  }

  size_t outDegree(Node* n) { return adj_[n].size(); }
};

/**
 * @brief Color class used by several graph algorithms.
 */
enum class Color { WHITE, GRAY, BLACK, RED };

/**
 * @brief Breadth first traversal.
 *
 *
 * Even if the function returns void some information is actually returned
 * inderectly in @a color, @a distance and @a predecesor.
 *
 * - @a color is a hash table mapping nodes in @a g to colors.
 * - @a distance is a hash table mapping nodes in @a g to an integer
 *   representing its distance from @a start.
 * - @a predecesor is a hash table mapping nodes in @a g to its closest
 *   predecesor.
 *
 * The caller is responsible for releasing the memory allocated to the returned
 * maps.
 */
template <typename Node, typename Edge>
void bfs(Graph<Node, Edge>* g, Node* start,
         unordered_map<Node*, Color>& coloring,
         unordered_map<Node*, size_t>& distance,
         unordered_map<Node*, Node*>& predecesor) {
  // Initialization
  for (Node* n : g->getNodes()) {
    coloring[n] = Color::WHITE;
    distance[n] = std::numeric_limits<size_t>::max();
    predecesor[n] = nullptr;
  }
  // BFS
  coloring[start] = Color::GRAY;
  distance[start] = 0;
  predecesor[start] = nullptr;

  queue<Node*> q;
  q.push(start);

  while (!q.empty()) {
    Node* u = q.front();
    for (Node* v : g->getAdjacentTo(u)) {
      if (coloring[v] == Color::WHITE) {
        coloring[v] = Color::GRAY;
        distance[v] = distance[u] + 1;
        predecesor[v] = u;
        q.push(v);
      }
    }
    q.pop();
    coloring[u] = Color::BLACK;
  }
}

/**
 * @brief DFS traversal implementation.
 *
 * Traverses @a g using DFS. The result are indirectly returned in:
 * - @a discovered: maps every node in @a g to its discovering time.
 * - @a finished: maps every node in the graph to the time when it is finished.
 * - @a predecessor: associates a node in the graph to its predecessor node
 *      according to DFS.
 */
template <typename Node, typename Edge>
void dfs(Graph<Node, Edge>* g, unordered_map<Node*, size_t>& discovered,
         unordered_map<Node*, size_t>& finished,
         unordered_map<Node*, Node*>& predecessor) {

  unordered_map<Node*, Color> coloring;
  size_t time = 0;
  for (Node* n : g->getNodes()) {
    coloring[n] = Color::WHITE;
    discovered[n] = numeric_limits<size_t>::max();
    finished[n] = numeric_limits<size_t>::max();
    predecessor[n] = nullptr;
  }

  for (Node* n : g->getNodes())
    if (coloring[n] == Color::WHITE)
      dfs_visit(g, n, coloring, discovered, finished, predecessor, time);
}

template <typename Node, typename Edge>
void dfs_visit(Graph<Node, Edge>* g, Node* n,
               unordered_map<Node*, Color>& coloring,
               unordered_map<Node*, size_t>& discovered,
               unordered_map<Node*, size_t>& finished,
               unordered_map<Node*, Node*>& predecessor, size_t& time) {
  coloring[n] = Color::GRAY;
  time++;
  discovered[n] = time;
  for (Node* m : g->getAdjacentTo(n))
    if (coloring[m] == Color::WHITE) {
      predecessor[m] = n;
      dfs_visit(g, m, coloring, discovered, finished, predecessor, time);
    }
  coloring[n] = Color::BLACK;
  time++;
  finished[n] = time;
}

/**
 * @brief Computes the transposed graph of @a g.
 *
 * The transposed graph of @a g called @a gt contains the same set of vertices
 * as @a g. For every edge (u,v) in g the edge (v,u) is in gt.
 */
template <typename Node, typename Edge>
Graph<Node, Edge>* transpose(Graph<Node, Edge>* g) {
  Graph<Node, Edge>* gt = new Graph<Node, Edge>();
  for (Node* n : g->getNodes()) gt->addNode(n);
  for (Edge* e : g->getEdges()) {
    Edge* ne = gt->addEdge(e->getEnd(), e->getStart());
    ne->setWeight(e->getWeight());
  }
  return gt;
}

/**
 * @brief Finds the strongly connected components of @a g
 *
 * Returns a map that associates Nodes to positive integers representing
 * their respective components. <n,i> means node N is in component i.
 */
template <typename Node, typename Edge>
unordered_map<Node*, size_t> scc(Graph<Node, Edge>* g) {
  /*
   * Prepare the call for the first DFS
   */
  unordered_map<Node*, size_t> discovered;
  unordered_map<Node*, size_t> finished;
  unordered_map<Node*, Node*> predecessor;

  dfs<Node, Edge>(g, discovered, finished, predecessor);

  // Compute the transposed graph
  Graph<Node, Edge>* gt = transpose<Node, Edge>(g);

  /*
   * We are interested in the finished mapping obtained from first DFS.
   * We need to iterate on the nodes in the inverse order in which they
   * were finished and use a map to sort them. Then we traverse the map
   * in reverse order and insert the nodes into a vector.
   */
  map<size_t, Node*> sortedNodes;
  for (pair<Node*, size_t> e : finished) sortedNodes[e.second] = e.first;

  vector<Node*> nodes;
  for (auto it = sortedNodes.rbegin(); it != sortedNodes.rend(); ++it)
    nodes.push_back(it->second);

  /* Now we run DFS again on gt. As we need to alter the order in which
   * dfs_visit is called we cannot directly use dfs. Notice that we need
   * to put every node WHITE in the coloring. Otherwise the new DFS will
   * not traverse it. We do not care about the other data structures as
   * they will be updated.
   */
  unordered_map<Node*, Color> coloring;
  size_t time = 0;
  for (Node* n : gt->getNodes()) coloring[n] = Color::WHITE;
  /*
   * scc will contain the map. cc is the connected component counter that
   * will change on every execution of dfs_visit. In order to distiguish
   * between nodes found by previous executions of dfs_visit we color
   * with red the nodes that already belong to a component. That way,
   * only those colored black belong to the current component.
   */
  unordered_map<Node*, size_t> scc;
  size_t cc = 0;
  for (Node* n : nodes) {
    if (coloring[n] == Color::WHITE) {
      dfs_visit(gt, n, coloring, discovered, finished, predecessor, time);
      for (pair<Node*, Color> e : coloring)
        if (e.second == Color::BLACK) {
          scc[e.first] = cc;
          coloring[e.first] = Color::RED;
        }
      cc++;
    }
  }
  return scc;
}

/**
 * @brief Export the graph in DOT format.
 *
 * Visit http://sandbox.kidstrythisathome.com/erdos/ to visualize it.
 */
template <typename Node, typename Edge>
void printDOT(ostream& os, Graph<Node, Edge>& g, bool weighted = false) {
  os << "digraph G {" << endl;

  for (Node* n : g.getNodes()) {
    os << "\t" << n->getId() << ";" << endl;
  }

  for (Edge* e : g.getEdges()) {
    string startId = e->getStart()->getId();
    string endId = e->getEnd()->getId();
    int weight = e->getWeight();
    os << "\t" << startId << " -> " << endId;
    if (weighted) os << "[label=" << weight << "]";
    os << ";" << endl;
  }
  os << "}" << endl;
}

/**
 * @brief Reads a graph from a file.
 *
 * The file specification is assumed to consists of one line per every edge in
 * the graph. Edges are specified by their end points separated by spaces.
 */
template <typename Node, typename Edge>
Graph<Node, Edge>* readFromFile(std::string fname, bool undirected = false) {
  Graph<Node, Edge>* g = new Graph<Node, Edge>();

  ifstream input(fname);
  string line;
  while (getline(input, line)) {
    if (line[0] == '#') continue;
    istringstream iss(line);
    vector<string> tokens{istream_iterator<string>{iss},
                          istream_iterator<string>{}};
    assert(tokens.size() == 2);
    if (!g->hasNodeWithId(tokens[0])) g->addNode(tokens[0]);
    if (!g->hasNodeWithId(tokens[1])) g->addNode(tokens[1]);
    g->addEdge(tokens[0], tokens[1]);
    if (undirected) g->addEdge(tokens[1], tokens[0]);
  }

  cout << "Graph statistics: " << endl;
  cout << "Number of nodes: " << g->numNodes() << endl;
  cout << "Number of edges: " << g->numEdges() << endl;

  return g;
}

template <typename Node>
Node* minKey(unordered_map<Node*, int>& distance,
             unordered_map<Node*, Color>& coloring) {
  int minDistance = numeric_limits<int>::max();
  Node* minNode = nullptr;
  for (pair<Node*, int> entry : distance) {
    Node* n = entry.first;
    int d = entry.second;
    if (coloring[n] == Color::WHITE && d < minDistance) {
      minDistance = distance[n];
      minNode = n;
    }
  }
  return minNode;
}
/**
 * @brief Computes the minimum spanning tree of @a g using Prim's algorithm.
 */
template <typename Node, typename Edge>
void prim(Graph<Node, Edge>* g, Node* start,
          unordered_map<Node*, Node*>& predecessor) {

  unordered_map<Node*, Color> coloring;
  unordered_map<Node*, int> distance;

  for (Node* n : g->getNodes()) {
    coloring[n] = Color::WHITE;
    distance[n] = numeric_limits<int>::max(); // key[n] = inf
    predecessor[n] = nullptr;
  }

  distance[start] = 0;
  int nodesInMST = 0;
  while (nodesInMST < g->numNodes()) {
    Node* u = minKey(distance, coloring);
    nodesInMST++;
    coloring[u] = Color::BLACK;
    for (Edge* e : g->getEdgesFrom(u)) {
      Node* v = e->getEnd();
      int weight = e->getWeight();
      if (coloring[v] == Color::WHITE && weight < distance[v]) {
        predecessor[v] = u;
        distance[v] = weight;
      }
    }
  }
}

// cout << "Finished\n";
// some data from: http://snap.stanford.edu/data/roadNet-PA.html
// Graph<Node, Edge>* g2 = readFromFile<Node, Edge>(
//    "/Users/ggutierrez/Work/edexamples/graphs/roadNet-PA.txt");

// some data from: http://snap.stanford.edu/data/amazon0302.html
// Graph<Node, Edge>* g2 = readFromFile<Node, Edge>(
//    "/Users/ggutierrez/Work/edexamples/graphs/amazon0302.txt");
//    return 0;
//}

#endif

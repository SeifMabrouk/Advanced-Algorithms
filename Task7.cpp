
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    vector<int> *adj; // Adjacency list for each vertex

    void fillOrder(int v, bool visited[], stack<int> &Stack);
    void DFSUtil(int v, bool visited[], vector<int> &component);

public:
    Graph(int V);
    void addEdge(int v, int w);
    vector<vector<int>> getSCCs();

    // Function to reverse the graph
    Graph getTranspose();
};

Graph::Graph(int V) {
    this->V = V;
    adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w) {
    adj[v].push_back(w);
}

void Graph::DFSUtil(int v, bool visited[], vector<int> &component) {
    visited[v] = true;
    component.push_back(v);

    for(int i = 0; i < adj[v].size(); ++i)
        if (!visited[adj[v][i]])
            DFSUtil(adj[v][i], visited, component);
}

Graph Graph::getTranspose() {
    Graph g(V);
    for (int v = 0; v < V; v++) {
        for(int i = 0; i < adj[v].size(); ++i) {
            g.adj[adj[v][i]].push_back(v);
        }
    }
    return g;
}

void Graph::fillOrder(int v, bool visited[], stack<int> &Stack) {
    visited[v] = true;
    for(int i = 0; i < adj[v].size(); i++)
        if(!visited[adj[v][i]])
            fillOrder(adj[v][i], visited, Stack);

    Stack.push(v);
}

vector<vector<int>> Graph::getSCCs() {
    stack<int> Stack;
    bool *visited = new bool[V];
    vector<vector<int>> sccs;

    for(int i = 0; i < V; i++)
        visited[i] = false;

    for(int i = 0; i < V; i++)
        if(visited[i] == false)
            fillOrder(i, visited, Stack);

    Graph gr = getTranspose();

    for(int i = 0; i < V; i++)
        visited[i] = false;

    while (!Stack.empty()) {
        int v = Stack.top();
        Stack.pop();

        if (visited[v] == false) {
            vector<int> component;
            gr.DFSUtil(v, visited, component);
            sccs.push_back(component);
        }
    }

    return sccs;
}

int main() {
    Graph g(5);
    g.addEdge(1, 0);
    g.addEdge(0, 2);
    g.addEdge(3, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 4);

    vector<vector<int>> sccs = g.getSCCs();

    vector<int> largestSCC;
    for (const auto &scc : sccs) {
        if (scc.size() > largestSCC.size()) {
            largestSCC = scc;
        }
    }

    cout << "The largest strongly connected component has " << largestSCC.size() << " vertices:" << endl;
    for (int v : largestSCC) {
        cout << v << " ";
    }
    cout << endl;

    return 0;
}

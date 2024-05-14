#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>

using namespace std;

class Graph {
private:
    int numVertices;
    unordered_map<int, vector<int>> adjList;

public:
    Graph(int n) {
        numVertices = n;
    }

    void addEdge(int src, int dest) {
        adjList[src].push_back(dest);
        adjList[dest].push_back(src); // If undirected graph
    }

    void displayAdjList() {
        cout << "Adjacency List:\n";
        for (auto it = adjList.begin(); it != adjList.end(); ++it) {
            cout << it->first << " -> ";
            for (int i = 0; i < it->second.size(); ++i) {
                cout << it->second[i] << " ";
            }
            cout << endl;
        }
    }

    void BFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(startVertex);
        visited[startVertex] = true;

        cout << "Breadth-First Search Traversal: ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";

            for (int i = 0; i < adjList[current].size(); ++i) {
                int neighbor = adjList[current][i];
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }

    void DFSUtil(int vertex, vector<bool> &visited) {
        visited[vertex] = true;
        cout << vertex << " ";

        for (int i = 0; i < adjList[vertex].size(); ++i) {
            int neighbor = adjList[vertex][i];
            if (!visited[neighbor]) {
                DFSUtil(neighbor, visited);
            }
        }
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        cout << "Depth-First Search Traversal: ";
        DFSUtil(startVertex, visited);
        cout << endl;
    }
};

int main() {
    int numVertices, numEdges;
    cout << "Enter the number of vertices in the graph: ";
    cin >> numVertices;
    cout << "Enter the number of edges in the graph: ";
    cin >> numEdges;

    Graph graph(numVertices);

    cout << "Enter the edges (source and destination vertices) in the graph:\n";
    for (int i = 0; i < numEdges; ++i) {
        int src, dest;
        cin >> src >> dest;
        graph.addEdge(src, dest);
    }

    graph.displayAdjList();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS traversals: ";
    cin >> startVertex;

    graph.BFS(startVertex);
    graph.DFS(startVertex);

    return 0;
}

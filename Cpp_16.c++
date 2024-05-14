#include <iostream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjMatrix;

public:
    Graph(int n) {
        numVertices = n;
        adjMatrix.resize(n, vector<int>(n, 0));
    }

    void addEdge(int src, int dest) {
        adjMatrix[src][dest] = 1;
        adjMatrix[dest][src] = 1; // If undirected graph
    }

    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                cout << adjMatrix[i][j] << " ";
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

            for (int i = 0; i < numVertices; ++i) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    q.push(i);
                    visited[i] = true;
                }
            }
        }
        cout << endl;
    }

    void DFS(int startVertex) {
        vector<bool> visited(numVertices, false);
        stack<int> stk;
        stk.push(startVertex);
        visited[startVertex] = true;

        cout << "Depth-First Search Traversal: ";
        while (!stk.empty()) {
            int current = stk.top();
            stk.pop();
            cout << current << " ";

            for (int i = 0; i < numVertices; ++i) {
                if (adjMatrix[current][i] == 1 && !visited[i]) {
                    stk.push(i);
                    visited[i] = true;
                }
            }
        }
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

    graph.displayAdjMatrix();

    int startVertex;
    cout << "Enter the starting vertex for BFS and DFS traversals: ";
    cin >> startVertex;

    graph.BFS(startVertex);
    graph.DFS(startVertex);

    return 0;
}

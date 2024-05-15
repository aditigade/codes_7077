#include <stdio.h>
#include <stdlib.h>

#define MAX 100

void createAdjMatrix(int Adj[][MAX], int N, int M);
void DFS(int Adj[][MAX], int N, int start);

int main() {
    int N, M;
    printf("Enter the number of vertices: ");
    scanf("%d", &N);
    printf("Enter the number of edges: ");
    scanf("%d", &M);

    int Adj[MAX][MAX] = {0}; // Adjacency matrix initialized to 0

    createAdjMatrix(Adj, N, M);

    int start;
    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &start);

    printf("DFS Traversal starting from vertex %d:\n", start);
    DFS(Adj, N, start);

    return 0;
}

void createAdjMatrix(int Adj[][MAX], int N, int M) {
    printf("Enter the edges (u v) where u and v are connected vertices:\n");
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        Adj[u][v] = 1;
        Adj[v][u] = 1; // Because the graph is undirected
    }
}

void DFS(int Adj[][MAX], int N, int start) {
    int visited[MAX] = {0}; // Visited array to keep track of visited vertices
    int stack[MAX], top = -1; // Stack and its top pointer

    // Push the start vertex onto the stack
    stack[++top] = start;

    while (top != -1) {
        // Pop a vertex from the stack
        int vertex = stack[top--];

        // If the vertex has not been visited, mark it as visited
        if (!visited[vertex]) {
            visited[vertex] = 1;
            printf("%d ", vertex);

            // Push all adjacent vertices of the popped vertex onto the stack
            for (int i = N; i >= 1; i--) {
                if (Adj[vertex][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
    printf("\n");
}

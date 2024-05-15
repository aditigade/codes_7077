#include <stdio.h>
#include <stdlib.h>

#define MAX 100  // Maximum number of vertices

void createAdjMatrix(int Adj[][MAX], int N, int M, int edges[][2]) {
    // Initialize adjacency matrix to 0
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            Adj[i][j] = 0;
        }
    }

    // Populate the adjacency matrix with edges
    for (int i = 0; i < M; i++) {
        int x = edges[i][0];
        int y = edges[i][1];
        Adj[x][y] = 1;
        Adj[y][x] = 1;
    }
}

void BFS(int Adj[][MAX], int N, int startVertex) {
    int visited[MAX] = {0};  // Array to keep track of visited vertices
    int queue[MAX], front = 0, rear = -1;
    int currentVertex;

    // Enqueue the start vertex and mark it as visited
    queue[++rear] = startVertex;
    visited[startVertex] = 1;

    printf("BFS Traversal: ");

    while (front <= rear) {
        // Dequeue a vertex from the queue
        currentVertex = queue[front++];
        printf("%d ", currentVertex);

        // Get all adjacent vertices of the dequeued vertex
        for (int i = 1; i <= N; i++) {
            if (Adj[currentVertex][i] == 1 && !visited[i]) {
                // Enqueue the adjacent vertex and mark it as visited
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }

    printf("\n");
}

int main() {
    int N, M;
    int edges[MAX][2];

    // Take input for number of vertices and edges
    printf("Enter the number of vertices: ");
    scanf("%d", &N);
    printf("Enter the number of edges: ");
    scanf("%d", &M);

    // Take input for the edges
    printf("Enter the edges (u v) format:\n");
    for (int i = 0; i < M; i++) {
        scanf("%d %d", &edges[i][0], &edges[i][1]);
    }

    int Adj[MAX][MAX];
    createAdjMatrix(Adj, N, M, edges);

    int startVertex;
    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);

    BFS(Adj, N, startVertex);

    return 0;
}
//Djikstra's algorithm
#include <iostream>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

int closest(int distance[], bool done[], int n);
void allPaths(int parent[], int distance[], int n, int source);
void printPath(int parent[], int node);

int main() {

	int n, source;
	cout << "No. of vertices in graph: ";
	cin >> n;
	

	int graph[n][n], parent[n], distance[n];
	bool done[n];
	memset(graph, 0, sizeof(graph));
	memset(parent, -1, sizeof(parent));
	memset(done, false, sizeof(done));
	for (int i = 0; i < n; ++i) {
		distance[i] = INT_MAX;
	}

	cout << "Input adjacency matrix for the graph:\n";
	for (int i = 0; i < n; ++i) {
		cout << i << ": ";
		for (int j = 0; j < n; ++j) {
			cin >> graph[i][j];
		}
	}

	cout << "Input source vertex: ";
	cin >> source;

	int u = -1;
	distance[source] = 0;
	for (int i = 0; i < n; ++i) {
		u = closest(distance, done, n);
		done[u] = true;
		for (int v = 0; v < n; ++v) {
			if (!done[v] && graph[u][v] && 
				(distance[u] + graph[u][v] < distance[v])) {
				parent[v] = u;
				distance[v] = distance[u] + graph[u][v];
			}
		}
	}

	allPaths(parent, distance, n, source);
	
	return 0;
}

int closest(int distance[], bool done[], int n) {
	int minm = 9999, min_index = -1;
	for (int i = 0; i < n; ++i) {
		if (!done[i] && distance[i] < minm) {
			minm = distance[i];
			min_index = i;
		}
	}
	return min_index;
}

void allPaths(int parent[], int distance[], int n, int source) {
	cout << "Shortest paths from source " << source << ":\n";
	for (int i = 0; i < n; ++i) {
		if (source == i)
			continue;
		else {
			cout << " to " << i << ": Distance = " << distance[i] << " Path: ";
			printPath(parent, i);
		}
		cout << '\n';
	}
}

void printPath(int parent[], int node) {
	if (parent[node] == -1)
		return;
	printPath(parent, parent[node]);
	cout << node << ' ';
}
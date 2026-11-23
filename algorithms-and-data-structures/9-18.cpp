#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge {
    int u;
    int v;
    int weight;
};

class DisjointSet {
private:
    vector<int> parent;
    vector<int> rank;

public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);

        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int vertex) {
        if (parent[vertex] != vertex) {
            parent[vertex] = find(parent[vertex]);
        }

        return parent[vertex];
    }

    bool unionSets(int a, int b) {
        int rootA = find(a);
        int rootB = find(b);

        if (rootA == rootB) {
            return false;
        }

        if (rank[rootA] < rank[rootB]) {
            parent[rootA] = rootB;
        } else if (rank[rootA] > rank[rootB]) {
            parent[rootB] = rootA;
        } else {
            parent[rootB] = rootA;
            rank[rootA]++;
        }

        return true;
    }
};

void kruskal(int vertices, vector<Edge>& edges) {
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    DisjointSet ds(vertices);

    vector<Edge> mst;
    int totalWeight = 0;

    for (const Edge& edge : edges) {
        if (ds.unionSets(edge.u, edge.v)) {
            mst.push_back(edge);
            totalWeight += edge.weight;
        }
    }

    cout << "Minimum Spanning Tree:\n";

    for (const Edge& edge : mst) {
        cout << edge.u << " - " << edge.v
            << " : " << edge.weight << endl;
    }

    cout << "Total weight: " << totalWeight << endl;
}

int main() {
    int vertices = 6;

    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 5},
        {2, 4, 11},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 1}
    };

    kruskal(vertices, edges);

    return 0;
}
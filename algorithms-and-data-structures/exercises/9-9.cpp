#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge {
    int to;
    int weight;
};

void dijkstra(int start, const vector<vector<Edge>>& graph) {
    int n = graph.size();

    vector<int> distance(n, INF);
    vector<int> previous(n, -1);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int currentVertex = pq.top().second;
        pq.pop();

        if (currentDistance > distance[currentVertex]) {
            continue;
        }

        for (const Edge& edge : graph[currentVertex]) {
            int nextVertex = edge.to;
            int newDistance = currentDistance + edge.weight;

            if (newDistance < distance[nextVertex]) {
                distance[nextVertex] = newDistance;
                previous[nextVertex] = currentVertex;
                pq.push({newDistance, nextVertex});
            }
        }
    }

    cout << "Shortest distances from vertex " << start << ":\n";

    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": ";

        if (distance[i] == INF) {
            cout << "unreachable";
        } else {
            cout << distance[i];
        }

        cout << endl;
    }
}

int main() {
    int vertices = 5;
    vector<vector<Edge>> graph(vertices);

    graph[0].push_back({1, 10});
    graph[0].push_back({3, 5});

    graph[1].push_back({2, 1});
    graph[1].push_back({3, 2});

    graph[2].push_back({4, 4});

    graph[3].push_back({1, 3});
    graph[3].push_back({2, 9});
    graph[3].push_back({4, 2});

    graph[4].push_back({0, 7});
    graph[4].push_back({2, 6});

    dijkstra(0, graph);

    return 0;
}
#include <bits/stdc++.h>

using namespace std;

struct Edge {
    long long v;
    long long w;
};

const auto INF = INT64_MAX;

typedef pair<long long, long long> pll;

long long Dijkstra(vector<vector<Edge>> &graph, long long start, long long finish) {
    vector<long long> distance(graph.size(), INF);
    distance[start] = 0;

    priority_queue<pll, std::vector<pll>, greater<>> min_heap;
    min_heap.push({0, start});
    while (!min_heap.empty()) {
        long long d = min_heap.top().first;
        long long u = min_heap.top().second;
        min_heap.pop();

        if (d > distance[u]) continue;

        for (auto& edge : graph[u]) {
            long long v = edge.v;
            long long w = edge.w;
            if (distance[u] + w < distance[v]) {
                distance[v] = distance[u] + w;
                min_heap.push({distance[v], v});
            }
        }
    }
    return distance[finish];
}

int main() {
    long long n, m, start, finish;
    cin >> n >> m >> start >> finish;

    vector<vector<Edge>> graph(n + 1, vector<Edge> ());
    for (int i = 0; i < m; ++i) {
        long long u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    long long result = Dijkstra(graph, start, finish);
    if (result == INF) {
        cout << "No solution\n";
    } else {
        cout << result << "\n";
    }
    return 0;
}
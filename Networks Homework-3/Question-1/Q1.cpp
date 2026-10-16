#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

class Graph {
private:
    map<string, vector<pair<string, int>>> adj;

public:
    void addEdge(const string& u, const string& v, int w) {
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    bool nodeExists(const string& node) {
        return adj.count(node) > 0;
    }

private:
    void printPath(const map<string, string>& parent,
                   const string& src, const string& dest) {
        vector<string> path;
        string cur = dest;

        // Tracing back from dest to src
        while (!cur.empty()) {
            path.push_back(cur);
            auto it = parent.find(cur);
            cur = (it != parent.end()) ? it->second : "";
        }

        if (path.back() != src) {
            cout << "No path found\n";
            return;
        }

        reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i + 1 < path.size()) cout << " -> ";
        }
        cout << "\n";
    }

public:
    // Dijkstra (Link State)
    void dijkstra(const string& src, const string& dest) {
        map<string, int> dist;
        map<string, string> parent;

        for (auto& [node, _] : adj) {
            dist[node] = INT_MAX;
            parent[node] = "";
        }
        dist[src] = 0;

        // Min-Heap: {cost, node}
        priority_queue<pair<int,string>,
                       vector<pair<int,string>>,
                       greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;

            for (auto& [v, w] : adj[u]) {
                if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        cout << "\nDijkstra (Link State)\n";
        if (dist[dest] == INT_MAX) {
            cout << "No path from " << src << " to " << dest << "\n";
            return;
        }
        cout << "Cost : " << dist[dest] << "\n";
        cout << "Path : ";
        printPath(parent, src, dest);
    }

    // Bellman-Ford (Distance Vector)
    void bellmanFord(const string& src, const string& dest) {
        map<string, int> dist;
        map<string, string> parent;

        for (auto& [node, _] : adj) {
            dist[node] = INT_MAX;
            parent[node] = "";
        }
        dist[src] = 0;

        int V = adj.size();

        // Relax all edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            bool updated = false;
            for (auto& [u, edges] : adj) {
                if (dist[u] == INT_MAX) continue;
                for (auto& [v, w] : edges) {
                    if (dist[u] + w < dist[v]) {
                        dist[v] = dist[u] + w;
                        parent[v] = u;
                        updated = true;
                    }
                }
            }
            if (!updated) break;
        }

        // Checking for negative weight cycles
        for (auto& [u, edges] : adj) {
            if (dist[u] == INT_MAX) continue;
            for (auto& [v, w] : edges) {
                if (dist[u] + w < dist[v]) {
                    cout << "\nNegative cycle detected\n";
                    return;
                }
            }
        }

        cout << "\nBellman-Ford (Distance Vector)\n";
        if (dist[dest] == INT_MAX) {
            cout << "No path from " << src << " to " << dest << "\n";
            return;
        }
        cout << "Cost : " << dist[dest] << "\n";
        cout << "Path : ";
        printPath(parent, src, dest);
    }
};

int main() {
    Graph g;

    // Graph from given question
    g.addEdge("E", "G", 1);
    g.addEdge("G", "H", 1);
    g.addEdge("H", "D", 1);
    g.addEdge("E", "D", 5);
    g.addEdge("E", "A", 1);
    g.addEdge("A", "B", 1);
    g.addEdge("B", "C", 1);
    g.addEdge("D", "K", 1);
    g.addEdge("K", "J", 1);
    g.addEdge("D", "F", 2);
    g.addEdge("F", "C", 3);
    g.addEdge("J", "C", 4);
    g.addEdge("G", "C", 1);

    string src, dest;
    cout << "Enter source node : ";
    cin  >> src;
    cout << "Enter destination node : ";
    cin  >> dest;

    if (!g.nodeExists(src) || !g.nodeExists(dest)) {
        cout << "One or both nodes not found in graph.\n";
        return 1;
    }

    g.dijkstra(src, dest);
    g.bellmanFord(src, dest);

    return 0;
}
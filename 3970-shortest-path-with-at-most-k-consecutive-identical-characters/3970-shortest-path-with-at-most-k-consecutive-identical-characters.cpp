class Solution {
public:
    int shortestPath(int n, vector<vector<int>>& edges, string labels, int k) {
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
        }

        // Min-heap priority queue storing tuples of (accumulated_weight, u, count)
        priority_queue<tuple<long long, int, int>, 
                       vector<tuple<long long, int, int>>, 
                       greater<tuple<long long, int, int>>> pq;

        // dist[u][count] stores the minimum weight to reach node u with `count` consecutive identical labels
        // count can range from 1 up to k
        vector<vector<long long>> dist(n, vector<long long>(k + 1, -1));

        // Start at node 0. The initial label count is 1.
        pq.push({0, 0, 1});
        dist[0][1] = 0;

        while (!pq.empty()) {
            auto [w, u, count] = pq.top();
            pq.pop();

            // If we reached the destination node, return the accumulated weight
            if (u == n - 1) {
                return w;
            }

            // If we found a shorter path to this state already, skip
            if (dist[u][count] != -1 && w > dist[u][count]) {
                continue;
            }

            // Explore neighbors
            for (auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                int next_count = (labels[u] == labels[v]) ? (count + 1) : 1;

                // Check constraints
                if (next_count <= k) {
                    long long next_weight = w + weight;

                    // If this is a better path to state (v, next_count), update and push
                    if (dist[v][next_count] == -1 || next_weight < dist[v][next_count]) {
                        dist[v][next_count] = next_weight;
                        pq.push({next_weight, v, next_count});
                    }
                }
            }
        }

        // If node n-1 is unreachable
        return -1;
    }
};
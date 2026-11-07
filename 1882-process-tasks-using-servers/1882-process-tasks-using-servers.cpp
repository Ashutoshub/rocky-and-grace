#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> assignTasks(vector<int>& servers, vector<int>& tasks) {
        int n = servers.size();
        int m = tasks.size();
        
        // free_servers: min-heap storing {weight, index}
        using FreeServer = pair<int, int>;
        priority_queue<FreeServer, vector<FreeServer>, greater<FreeServer>> free_servers;
        
        for (int i = 0; i < n; ++i) {
            free_servers.push({servers[i], i});
        }
        
        // busy_servers: min-heap storing {available_time, weight, index}
        // Using long long for available_time to prevent integer overflow
        using BusyServer = tuple<long long, int, int>;
        priority_queue<BusyServer, vector<BusyServer>, greater<BusyServer>> busy_servers;
        
        vector<int> ans(m);
        long long current_time = 0;
        
        for (int j = 0; j < m; ++j) {
            // Task j cannot start before second j
            current_time = max(current_time, static_cast<long long>(j));
            
            // Release all servers that have finished their tasks by current_time
            while (!busy_servers.empty() && get<0>(busy_servers.top()) <= current_time) {
                auto [time, weight, idx] = busy_servers.top();
                busy_servers.pop();
                free_servers.push({weight, idx});
            }
            
            // If no servers are available, jump time to the earliest completing server
            if (free_servers.empty()) {
                current_time = get<0>(busy_servers.top());
                while (!busy_servers.empty() && get<0>(busy_servers.top()) <= current_time) {
                    auto [time, weight, idx] = busy_servers.top();
                    busy_servers.pop();
                    free_servers.push({weight, idx});
                }
            }
            
            // Pick the best available server
            auto [weight, server_idx] = free_servers.top();
            free_servers.pop();
            
            ans[j] = server_idx;
            
            // Push to busy heap with next available time
            busy_servers.push({current_time + tasks[j], weight, server_idx});
        }
        
        return ans;
    }
};
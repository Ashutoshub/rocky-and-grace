class Solution {
public:
    int minMoves(vector<string>& classroom, int energy) {
        int m = classroom.size();
        int n = classroom[0].size();
        
        int startX = -1, startY = -1;
        int l_count = 0;
        
        // Map to quickly find the bit-index of a specific litter
        int L_index[20][20];
        for(int i = 0; i < 20; ++i) {
            for(int j = 0; j < 20; ++j) {
                L_index[i][j] = -1;
            }
        }
        
        // 1. Scan the grid for Start and Litter
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (classroom[i][j] == 'S') {
                    startX = i;
                    startY = j;
                } else if (classroom[i][j] == 'L') {
                    L_index[i][j] = l_count++;
                }
            }
        }
        
        int target_mask = (1 << l_count) - 1; 
        if (target_mask == 0) return 0; // Edge case: No litter to clean
        
        // bestEnergy[x][y][mask] stores the maximum energy we've had at this state
        // Initialized to -1
        vector<vector<vector<int>>> bestEnergy(m, vector<vector<int>>(n, vector<int>(1 << l_count, -1)));
        
        // Queue stores: tuple<x, y, mask, current_energy, steps>
        queue<tuple<int, int, int, int, int>> q;
        
        q.push({startX, startY, 0, energy, 0});
        bestEnergy[startX][startY][0] = energy;
        
        // Direction arrays for Up, Down, Left, Right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        while (!q.empty()) {
            auto [x, y, mask, e, steps] = q.front();
            q.pop();
            
            // If we have collected all litter, BFS guarantees this is the minimum steps
            if (mask == target_mask) {
                return steps;
            }
            
            // If we have 0 energy, we cannot move to an adjacent cell
            if (e == 0) continue; 
            
            for (int i = 0; i < 4; ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                // Check bounds and obstacles
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && classroom[nx][ny] != 'X') {
                    int next_e = e - 1;
                    int next_mask = mask;
                    
                    // Update mask if we stepped on litter
                    if (L_index[nx][ny] != -1) {
                        next_mask |= (1 << L_index[nx][ny]);
                    }
                    
                    // Reset energy if we stepped on a Reset space
                    if (classroom[nx][ny] == 'R') {
                        next_e = energy;
                    }
                    
                    // Pruning: Only proceed if this path offers strictly better remaining energy 
                    // for this specific location and mask combination.
                    if (next_e > bestEnergy[nx][ny][next_mask]) {
                        bestEnergy[nx][ny][next_mask] = next_e;
                        q.push({nx, ny, next_mask, next_e, steps + 1});
                    }
                }
            }
        }
        
        // If the queue empties and we haven't returned, it's impossible.
        return -1;
    }
};
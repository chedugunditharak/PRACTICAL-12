#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// High value representing infinity for unreachable nodes
const int INF = 1e9; 

int solveTSP(const vector<vector<int>>& cost) {
    int n = cost.size();
    
    // Total states = 2^n. Every bit mask represents a subset of visited cities.
    int numStates = 1 << n; 
    
    // dp[mask][i] stores the min cost to visit the subset of cities in 'mask', 
    // ending at city 'i'.
    vector<vector<int>> dp(numStates, vector<int>(n, INF));
    
    // Base Case: Start at city 0. Only city 0 is visited. Cost is 0.
    dp[1][0] = 0; 
    
    // Iterate through all possible subsets (masks) of cities
    for (int mask = 1; mask < numStates; ++mask) {
        for (int u = 0; u < n; ++u) {
            // If city 'u' is not in the current subset, skip
            if (!(mask & (1 << u))) continue;
            
            // If the current state is unreachable, skip
            if (dp[mask][u] == INF) continue;
            
            // Try to move to any unvisited city 'v'
            for (int v = 0; v < n; ++v) {
                // If city 'v' is already visited, skip
                if (mask & (1 << v)) continue;
                
                // Calculate the new mask with city 'v' included
                int nextMask = mask | (1 << v);
                
                // Transition: update the next state with the minimal cost
                dp[nextMask][v] = min(dp[nextMask][v], dp[mask][u] + cost[u][v]);
            }
        }
    }
    
    // Find the minimum cost to complete the tour by returning to city 0
    int minCost = INF;
    int fullMask = numStates - 1; // All bits are 1 (all cities visited)
    
    for (int i = 1; i < n; ++i) {
        if (dp[fullMask][i] != INF) {
            minCost = min(minCost, dp[fullMask][i] + cost[i][0]);
        }
    }
    
    return minCost;
}

int main() {
    // Distance matrix / Cost adjacency matrix representing 4 cities
    vector<vector<int>> cost = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    
    int result = solveTSP(cost);
    
    cout << "Minimum TSP Tour Cost: " << result << endl;
    cout << "Enrollment No:92460118181";
    
    return 0;
}

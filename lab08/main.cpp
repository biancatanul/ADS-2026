#include <iostream>
#include <vector>
#include <unordered_map>

// reusable DSU
struct DSU {
    std::vector<int> parent, rank, size;

    DSU(int n) : parent(n), rank(n, 0), size(n, 1) {
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    // path compression
    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // union by rank , returns false if already same set
    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry]) std::swap(rx, ry);
        parent[ry] = rx;
        size[rx] += size[ry];
        if (rank[rx] == rank[ry]) rank[rx]++;
        return true;
    }
};

// exercise 1: count connected components

int countComponents(int n, std::vector<std::pair<int,int>>& edges) {
    DSU dsu(n);
    int components = n;
    for (auto& [u, v] : edges)
        if (dsu.unite(u, v))
            components--;
    return components;
}

// exercise 2: detect cycle in undirected graph

bool hasCycle(int n, std::vector<std::pair<int,int>>& edges) {
    DSU dsu(n);
    for (auto& [u, v] : edges) {
        if (dsu.find(u) == dsu.find(v))
            return true;
        dsu.unite(u, v);
    }
    return false;
}

// exercise 3: number of provinces (adjacency matrix input)

int findProvinces(std::vector<std::vector<int>>& isConnected) {
    int n = isConnected.size();
    DSU dsu(n);
    int provinces = n;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (isConnected[i][j] == 1 && dsu.unite(i, j))
                provinces--;
    return provinces;
}

// exercise 4: friend groups with sizes and members

void friendGroups(int n, std::vector<std::pair<int,int>>& friendships) {
    DSU dsu(n);
    for (auto& [a, b] : friendships)
        dsu.unite(a, b);

    std::unordered_map<int, std::vector<int>> groups;
    for (int i = 0; i < n; i++)
        groups[dsu.find(i)].push_back(i);

    std::cout << groups.size() << " Groups\n";
    int g = 1;
    for (auto& [root, members] : groups) {
        std::cout << "Group " << g++ << ": {";
        for (int i = 0; i < (int)members.size(); i++) {
            std::cout << members[i];
            if (i + 1 < (int)members.size()) std::cout << ",";
        }
        std::cout << "} size " << members.size() << "\n";
    }
}

// main: test all exercises
int main() {
    // exercise 1
    std::cout << "Exercise 1: Connected components\n";
    int n1 = 5;
    std::vector<std::pair<int,int>> edges1 = {{0,1},{1,2},{3,4}};
    std::cout << "Components: " << countComponents(n1, edges1) << "\n\n";

    // exercise 2
    std::cout << "Exercise 2: Cycle detection\n";
    int n2 = 4;
    std::vector<std::pair<int,int>> edges2_cycle = {{0,1},{1,2},{2,0}};
    std::vector<std::pair<int,int>> edges2_no_cycle = {{0,1},{1,2},{2,3}};
    std::cout << "Graph with cycle:    " << (hasCycle(n2, edges2_cycle)    ? "YES" : "NO") << "\n";
    std::cout << "Graph without cycle: " << (hasCycle(n2, edges2_no_cycle) ? "YES" : "NO") << "\n\n";

    // exercise 3
    std::cout << "Exercise 3: Provinces\n";
    std::vector<std::vector<int>> isConnected = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    std::cout << "Provinces: " << findProvinces(isConnected) << "\n\n";

    // exercise 4
    std::cout << "Exercise 4: Friend groups\n";
    int n4 = 7;
    std::vector<std::pair<int,int>> friendships = {{0,1},{1,2},{3,4},{5,6}};
    friendGroups(n4, friendships);

    return 0;
}
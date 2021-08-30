#include <queue>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
using Graph = vector<vector<char>>;

int minCost(string &s, char t, Graph &g) {
    vector<int> cost(256, -1);
    queue<char> q;
    
    q.push(t), cost[t] = 0;
    while (!q.empty()) {
        char u = q.front(); q.pop();
        for (char v: g[u]) if (cost[v] == -1) {
            q.push(v), cost[v] = 1 + cost[u];
        }
    }

    int res = 0;
    for (char c: s) {
        if (cost[c] == -1) return -1;
        res += cost[c];
    }

    return res;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        string s; fin >> s;
        int k; fin >> k;
        Graph g(256);

        while (k--) {
            string t; fin >> t;
            g[t[1]].push_back(t[0]);
        }

        int ans = -1;
        for (char c = 'A'; c <= 'Z'; c++) {
            int x = minCost(s, c, g);
            if (x == -1) continue;
            if (ans == -1 || x < ans) ans = x;
        }
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

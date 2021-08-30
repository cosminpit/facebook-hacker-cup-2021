#include <vector>
#include <fstream>
using namespace std;
using Graph = vector<vector<int>>;

int dfs(int u, int p, Graph &g, vector<int> &c) {
    int m1 = 0, m2 = 0;
    for (int v: g[u]) if (v != p) {
        int m3 = dfs(v, u, g, c);
        if (m3 > m2) swap(m3, m2);
        if (m2 > m1) swap(m2, m1);
    }
    return (u == 0) ? (c[u] + m1 + m2) : (m1 + c[u]);
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        vector<int> c(n);
        Graph g(n);

        for (int i = 0; i < n; i++) fin >> c[i];
        for (int i = 1; i < n; i++) {
            int u, v; fin >> u >> v; u--; v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        
        fout << "Case #" << test << ": " << dfs(0, -1, g, c) << "\n";
    }
    return 0;
}

#include <map>
#include <vector>
#include <fstream>
using namespace std;
using Graph = vector<vector<int>>;

struct Result {
    int onlyInThisTree;
    map<int, int> count;
};

Result dfs(int u, int p, Graph &g, vector<int> &f, map<int, int> &all, int &ans) {
    Result ru;
    ru.onlyInThisTree = (all[f[u]] == 1);
    ru.count[f[u]] = 1;
    for (int v: g[u]) if (v != p) {
        Result rv = dfs(v, u, g, f, all, ans);

        if (ru.count.size() < rv.count.size()) { 
            swap(ru.onlyInThisTree, rv.onlyInThisTree);
            ru.count.swap(rv.count);
        }

        for (const auto &e: rv.count) {
            ru.count[e.first] += e.second;
            ru.onlyInThisTree += (ru.count[e.first] == all[e.first]);
        }
    }
    if (p != -1 && ru.onlyInThisTree == ru.count.size()) ans++;
    return ru;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        map<int, int> all;
        vector<int> f(n);
        Graph g(n);

        for (int i = 1; i < n; i++) {
            int u, v; fin >> u >> v; u--; v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        for (int u = 0; u < n; u++) {
            fin >> f[u]; all[f[u]]++;
        }

        int ans = 0;
        dfs(0, -1, g, f, all, ans);

        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

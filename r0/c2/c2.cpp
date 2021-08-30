#include <vector>
#include <fstream>
using namespace std;
using Graph = vector<vector<int>>;

struct Result {
    int dp[55][2][2];
};

void update(int &x, int y) {
    x = max(x, y);
}

Result dfs(int u, int p, Graph &g, vector<int> &c, int k) {
    Result ru = {0};
    ru.dp[0][1][1] = c[u];
    for (int v: g[u]) if (v != p) {
        Result rv = dfs(v, u, g, c, k);
        Result r = {0};
        for (int ku = 0; ku <= k; ku++)
            for (int kv = 0; ku + kv <= k; kv++) {
                update(r.dp[ku + kv][0][0], ru.dp[ku][0][0] + rv.dp[kv][0][0]);
                update(r.dp[ku + kv][0][0], ru.dp[ku][0][0] + rv.dp[kv][1][0]);
                update(r.dp[ku + kv][1][1], c[u] + ru.dp[ku][0][0] + rv.dp[kv][1][1]);

                update(r.dp[ku + kv][1][0], ru.dp[ku][1][0] + rv.dp[kv][0][0]);
                update(r.dp[ku + kv][1][0], ru.dp[ku][1][0] + rv.dp[kv][1][0]);
                update(r.dp[ku + kv][1][1], ru.dp[ku][1][0] + rv.dp[kv][1][1]);

                update(r.dp[ku + kv][1][1], ru.dp[ku][1][1] + rv.dp[kv][0][0]);
                update(r.dp[ku + kv][1][1], ru.dp[ku][1][1] + rv.dp[kv][1][0]);
                update(r.dp[ku + kv + 1][1][0], ru.dp[ku][1][1] + rv.dp[kv][1][1]);
            }
        ru = r;
    }
    for (int ku = 0; ku <= k; ku++) {
        update(ru.dp[ku + 1][1][0], ru.dp[ku][1][1]);
    }
    return ru;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, k; fin >> n >> k;
        vector<int> c(n);
        Graph g(n);

        for (int i = 0; i < n; i++) fin >> c[i];
        for (int i = 1; i < n; i++) {
            int u, v; fin >> u >> v; u--; v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }

        Result res = dfs(0, -1, g, c, k);
        int ans = 0;
        for (int i = 0; i <= k; i++) ans = max(ans, res.dp[i][1][0]);
        fout << "Case #" << test << ": " << ((k == 0) ? c[0] : ans) << "\n";
    }
    return 0;
}

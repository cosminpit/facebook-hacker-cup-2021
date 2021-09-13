#include <vector>
#include <cstdint>
#include <fstream>
using namespace std;
using Graph = vector<vector<pair<int, int>>>;
const int MOD = 1'000'000'007;

struct Result {
    int64_t sum;
    int64_t count[21];
};

Result extend(Result x, int w) {
    x.count[w] = x.count[w] + 1;
    for (int i = w + 1; i <= 20; i++) {
        x.count[w] = x.count[w] + x.count[i];
        x.count[i] = 0;
    }

    for (int i = 0; i <= 20; i++)
        x.sum = (x.sum + i*x.count[i])%MOD;

    return x;
}

void combine(Result &x, const Result &y) {
    x.sum = (x.sum + y.sum)%MOD;
    for (int i = 0; i <= 20; i++)
        for (int j = 0; j <= 20; j++)
            x.sum = (x.sum + min(i, j)*x.count[i]*y.count[j])%MOD;

    for (int i = 0; i <= 20; i++)
        x.count[i] = x.count[i] + y.count[i];
}

void dfs1(int u, int p, const Graph &g, vector<Result> &dp) {
    memset(&dp[u], 0, sizeof(Result));
    for (const auto &e: g[u]) {
        int v = e.first, w = e.second;
        if (v == p) continue;
        dfs1(v, u, g, dp);
        combine(dp[u], extend(dp[v], w));
    }
}

void dfs2(int u, int p, const Result &up, const Graph &g, const vector<Result> &dp, int64_t &ans) {
    Result dummy = {0};
    vector<Result> right(g[u].size() + 1, dummy);
    for (int k = g[u].size() - 1; k >= 0; k--) {
        int v = g[u][k].first, w = g[u][k].second;
        right[k] = right[k + 1];
        if (v == p) continue;
        combine(right[k], extend(dp[v], w));
    }

    Result left = up;
    for (int k = 0; k < g[u].size(); k++) {
        int v = g[u][k].first, w = g[u][k].second;
        if (v == p) continue;

        Result new_up = left;
        combine(new_up, right[k + 1]);
        dfs2(v, u, extend(new_up, w), g, dp, ans);
        ans = ans*((new_up.sum + dp[v].sum)%MOD)%MOD;
        
        combine(left, extend(dp[v], w));
    }
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        Graph g(n);
        vector<Result> dp(n);

        for (int i = 1; i < n; i++) {
            int u, v, w; fin >> u >> v >> w; u--; v--;
            g[u].push_back({v, w});
            g[v].push_back({u, w});
        }

        Result up = {0};
        int64_t ans = 1;
        dfs1(0, -1, g, dp);
        dfs2(0, -1, up, g, dp, ans);

        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

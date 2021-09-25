#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void simulate(vector<string> &g, int k, int &ans) {
    g.push_back(string(g[0].size(), '.'));

    int nr = g.size(), nc = g[0].size();
    vector<int> avail(nc, 0);
    for (int r = 0; r < k; r++)
        for (int c = 0; c < nc; c++)
            avail[c] += (g[r][c] == '.');

    string state = g[k];
    for (int r = k + 1; r < nr; r++) {
        for (int c = 0; c < nc; c++) {
            if (state[c] == '.') {
                state[c] = g[r][c];
            } else if (avail[c]) {
                avail[c]--;
                state[c] = g[r][c];
            }
        }

        int cost = r - k;
        for (char e: state) cost += (e == 'X');
        ans = min(ans, cost);
    }

    g.pop_back();
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int nr, nc, k; fin >> nr >> nc >> k; k--;
        vector<string> g(nr);

        for (int r = 0; r < nr; r++) fin >> g[r];

        int ans = 0;
        for (char e: g[k]) ans += (e == 'X');

        simulate(g, k, ans);
        for (int c = 0; c < nc; c++)
            for (int u = 0, v = nr - 1; u < v; u++, v--)
                swap(g[u][c], g[v][c]);
        simulate(g, nr - k - 1, ans);

        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

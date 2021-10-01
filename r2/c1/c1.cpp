#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void simulate(vector<string> &g, int k, int &ans) {
    g.push_back(string(g[0].size(), '.'));

    int nr = g.size(), nc = g[0].size();
    vector<int> count(nc, 0);
    for (int r = 0; r < k; r++)
        for (int c = 0; c < nc; c++)
            count[c] += (g[r][c] == 'X');

    for (int r = k; r < nr; r++) {
        int cost = r - k;
        for (int c = 0; c < nc; c++) {
            count[c] += (g[r][c] == 'X');
            cost += ((g[r][c] == 'X') || (count[c] > k));
        }
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

        int ans = nc;
        simulate(g, k, ans);
        reverse(g.begin(), g.end());
        simulate(g, nr - k - 1, ans);

        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

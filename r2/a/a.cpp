#include <map>
#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, m; fin >> n >> m;
        vector<int> s(m), used(m);
        for (int i = 0; i < m; i++) fin >> s[i];

        int ans = 0;
        while (n--) {
            map<int, int> c;
            for (int i = 0; i < m; i++) {
                int k; fin >> k; c[k]++;
            }

            vector<int> unmatched;
            for (int i = 0; i < m; i++) if (used[i]) {
                if (c[s[i]]) {
                    c[s[i]]--;
                } else {
                    unmatched.push_back(i);
                }
            }
            for (int i = 0; i < m; i++) if (!used[i]) {
                if (c[s[i]]) {
                    c[s[i]]--;
                } else {
                    unmatched.push_back(i);
                }
            }

            auto it = c.begin();
            for (int i: unmatched) {
                while (it->second == 0) it++;
                s[i] = it->first; it->second--;
                if (used[i]) ans++;
                used[i] = 1;
            }
        }

        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

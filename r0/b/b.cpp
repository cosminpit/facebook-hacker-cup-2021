#include <map>
#include <set>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        vector<string> c(n);
        map<int, set<vector<pair<int, int>>>> wins;

        for (int i = 0; i < n; i++) fin >> c[i];

        for (int i = 0; i < n; i++) {
            bool canWin = true;
            vector<pair<int, int>> moves;
            for (int j = 0; j < n && canWin; j++) {
                switch (c[i][j]) {
                    case 'O': canWin = false; break;
                    case 'X': break;
                    case '.': moves.push_back({i, j}); break;
                }
            }
            if (canWin) wins[moves.size()].insert(moves);
        }

        for (int j = 0; j < n; j++) {
            bool canWin = true;
            vector<pair<int, int>> moves;
            for (int i = 0; i < n && canWin; i++) {
                switch (c[i][j]) {
                    case 'O': canWin = false; break;
                    case 'X': break;
                    case '.': moves.push_back({i, j}); break;
                }
            }
            if (canWin) wins[moves.size()].insert(moves);
        }

        fout << "Case #" << test << ": ";
        if (wins.empty()) {
            fout << "Impossible\n";
        } else {
            fout << wins.begin()->first << " " << wins.begin()->second.size() << "\n";
        }
    }
    return 0;
}

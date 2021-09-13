#include <vector>
#include <fstream>
using namespace std;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n, m, a, b; fin >> n >> m >> a >> b;
        int x = a - (n + m - 2);
        int y = b - (n + m - 2);
        fout << "Case #" << test << ": ";
        if (x <= 0 || y <= 0) {
            fout << "Impossible\n";
        } else {
            fout << "Possible\n";
            vector<vector<int>> r(n, vector<int>(m, 1));
            r[0][0] = x; r[0][m - 1] = y;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    fout << r[i][j] << " ";
                }
                fout << "\n";
            }
        }
    }
    return 0;
}

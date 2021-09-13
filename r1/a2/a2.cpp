#include <vector>
#include <string>
#include <fstream>
using namespace std;
const int MOD = 1'000'000'007;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        string s; fin >> s;
        long long ans = 0, sum = 0;
        for (int i = 1, j = 0; i < n; i++) {
            if (s[i] == 'F' || s[i] == s[j] || s[j] == 'F') {
                j = (s[i] != 'F') ? i : j;
            } else {
                sum = (sum + j + 1)%MOD;
                j = i;
            }
            ans = (ans + sum)%MOD;
        }
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

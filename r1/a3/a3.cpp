#include <vector>
#include <string>
#include <fstream>
using namespace std;
const long long MOD = 1'000'000'007;

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        string s; fin >> s;
        long long ans = 0, sum_suff = 0, sum_pref = 0, cost = 0, fi = 0, li = 0;
        char fc = 'F', lc = 'F';

        n = 0;
        for (char c: s) {
            if (c == '.') {
                long long k1 = (lc != 'F') ? (li + 1)%MOD : 0;
                long long k2 = (fc != 'F') ? (n - fi + MOD)%MOD : 0;
                long long extra = (fc != lc);
                if (!extra) k1 = 0, k2 = 0;
                ans = (ans + ans + sum_suff*n%MOD + sum_pref*n%MOD + k1*k2%MOD)%MOD;
                sum_suff = (sum_suff + (sum_suff + n*cost%MOD + k1))%MOD;
                sum_pref = (sum_pref + (sum_pref + n*cost%MOD + k2))%MOD;
                cost = (cost + cost + extra)%MOD;
                li = (n + li)%MOD;
                n = (n + n)%MOD;
            } else if (c == 'F' || c == lc || lc == 'F') {
                ans = (ans + sum_suff)%MOD;
                sum_pref = (sum_pref + cost)%MOD;
                if (fc == 'F' && c != 'F') fc = c, fi = n;
                if (c != 'F') lc = c, li = n;
                n = (n + 1)%MOD;
            } else {
                cost = (cost + 1)%MOD;
                sum_pref = (sum_pref + cost)%MOD;
                sum_suff = (sum_suff + li + 1)%MOD;
                ans = (ans + sum_suff)%MOD;
                lc = c, li = n;
                n = (n + 1)%MOD;
            }
        }
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

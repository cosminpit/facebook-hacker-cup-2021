#include <string>
#include <fstream>
using namespace std;

bool isVowel(char c) {
    return c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U';
}

int cost(string &s, char t) {
    int res = 0;
    for (char c: s) {
        if (c == t) continue;
        res += (isVowel(c) == isVowel(t)) ? 2 : 1;
    }
    return res;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        string s; fin >> s;
        int ans = 2*s.size() + 1;
        for (char c = 'A'; c <= 'Z'; c++) {
            ans = min(ans, cost(s, c));
        }
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

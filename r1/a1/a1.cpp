#include <string>
#include <fstream>
using namespace std;

int cost(string &s, char h) {
    int res = 0;
    for (char c: s) {
        if (c != 'F' && c != h) res++, h = c;
    }
    return res;
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int n; fin >> n;
        string s; fin >> s;
        int ans = min(cost(s, 'O'), cost(s, 'X'));
        fout << "Case #" << test << ": " << ans << "\n";
    }
    return 0;
}

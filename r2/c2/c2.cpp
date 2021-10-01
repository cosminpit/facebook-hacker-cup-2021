#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <algorithm>
using namespace std;

struct FenTree {
    vector<int> t;

    FenTree(int n): t(n + 1) {}

    int prefix(int i) {
        int res = 0;
        for (i++; i > 0; i -= i & -i) res += t[i];
        return res;
    }

    int indexOfPrefixAtLeast(int sum) {
        int i = 0, bit = 1;
        while (bit < t.size()) bit *= 2;
        for (; bit; bit /= 2)
            if (i + bit < t.size() && t[i + bit] < sum)
                i += bit, sum -= t[i];
        return i; 
    }

    int get(int i) {
        return prefix(i) - prefix(i - 1);
    }

    void add(int i, int x) {
        for (i++; i < t.size(); i += i & -i) t[i] += x;
    }

    void set(int i, int x) {
        add(i, x - get(i));
    }
};

struct SegTree {
    int a, b, min, lazy;
    unique_ptr<SegTree> l, r;

    SegTree(int a, int b, int v): a(a), b(b), min(v), lazy(0) {
        if (a != b) {
            int m = (a + b)/2;
            l = unique_ptr<SegTree>(new SegTree(a, m, v));
            r = unique_ptr<SegTree>(new SegTree(m + 1, b, v));
        }
    }

    void pushLazy() {
        if (lazy) {
            min += lazy;
            if (l) l->lazy += lazy, r->lazy += lazy;
            lazy = 0;
        }
    }

    int getMin(int x, int y) {
        pushLazy();
        if (b < x || y < a) return numeric_limits<int>::max();
        if (x <= a && b <= y) return min;
        return std::min(l->getMin(x, y), r->getMin(x, y));
    }
    
    void add(int x, int y, int v) {
        pushLazy();
        if (b < x || y < a) return;
        if (x <= a && b <= y) {
            lazy = v;
        } else {
            l->add(x, y, v);
            r->add(x, y, v);
            min = std::min(l->min + l->lazy, r->min + r->lazy);
        }
    }
};

void solve(int nr, int nc, int k, vector<pair<int, int>> flips, vector<int> &ans) {
    SegTree seg(0, nr, 0);
    vector<FenTree> col;

    for (int c = 0; c  < nc; c++) col.push_back(FenTree(nr + 1));
    for (int r = k; r <= nr; r++) seg.add(r, r, r - k);

    for (int i = 0; i < flips.size(); i++) {
        int r, c; tie(r, c) = flips[i];
        FenTree &fen = col[c];
        int val = fen.get(r);

        int x = fen.indexOfPrefixAtLeast(k + 1);
        fen.set(r, 1 - val);
        int y = fen.indexOfPrefixAtLeast(k + 1);

        if ( val && x + 1 <= y - 1) seg.add(x + 1, y - 1, -1);
        if (!val && y + 1 <= x - 1) seg.add(y + 1, x - 1, +1);
        if (r <= min(x, y)) seg.add(r, r, val ? -1 : +1);

        ans[i] = min(ans[i], seg.getMin(k, nr));
    }
}

int main() {
    ifstream fin("in.txt");
    ofstream fout("out.txt");
    int nTests; fin >> nTests;
    for (int test = 1; test <= nTests; test++) {
        int nr, nc, k, s; fin >> nr >> nc >> k >> s; k--;
        vector<pair<int, int>> flips;

        for (int r = 0; r < nr; r++) {
            string row; fin >> row;
            for (int c = 0; c < nc; c++)
                if (row[c] == 'X') flips.push_back({r, c});
        }

        for (int i = 0; i < s; i++) {
            int r, c; fin >> r >> c; r--; c--;
            flips.push_back({r, c});
        }

        vector<int> ans(flips.size(), nc);
        solve(nr, nc, k, flips, ans);
        for (auto &p: flips) p.first = nr - p.first - 1;
        solve(nr, nc, nr - k - 1, flips, ans);

        long long res = 0;
        for (int i = ans.size() - s; i < ans.size(); i++) res += ans[i];

        fout << "Case #" << test << ": " << res << "\n";
    }
    return 0;
}

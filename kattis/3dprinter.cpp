#include <iostream>
#include <vector>

using namespace std;

inline int ceilDivide(int x, int y) {
    return (x+y-1)/y;
}

int main() {
    int n; cin >> n;
    int mn = n;
    for (int p = 1, pow2 = 1, moves = 1; p <= n; ++p) {
        if (p == 2*pow2) pow2 = p, ++moves;
        int remaining = n - ((2*pow2-p));
        mn = min(mn, moves + ceilDivide(remaining, p));
    }
    cout << mn << endl;
    return 0;
}

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

const int N = 250;

int main() {
    int n; cin >> n;
    vector<vector<bool>> v(n, vector<bool>(n+1));
    for (int i = 1; i <= n; ++i) {
        int x;
        while (cin >> x && x != -1) v[x-1][i-1] = 1;
    }
    for (int i = 0; i < n; ++i) v[i][n] = 1;

    // gaussian elimination
    for (int i = 0; i < n; ++i) {
        int k = i;
        for (int j = i+1; j < n; ++j) {
            if (v[j][i] > v[k][i]) k = j;
        }
        swap(v[k], v[i]);
        assert(v[i][i]);
        for (int j = i+1; j < n; ++j) {
            if (v[j][i]) {
                for (int l = i; l <= n; ++l) {
                    v[j][l] = v[j][l] ^ v[i][l]; // subtract
                }
            }
        }
    }

    for (int i = n-1; i >= 0; --i) {
        for (int j = i+1; j < n; ++j) {
            if (v[i][j]) v[i][n] = v[i][n] ^ v[j][n]; // subtract
        }
    }

    for (int i = 0; i < n; ++i) {
        if (v[i][n]) cout << i+1 << ' ';
    }
    cout << endl;
    return 0;
}

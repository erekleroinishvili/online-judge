// Divide and Conquer DP Optimisation
#include <bits/stdc++.h>

using namespace std;

const long long INF = 1e18;
vector<int> a, p;
vector<vector<long long>> cost;
void solve(int parts, int l, int r, int optl, int optr) {
    if (l > r) return;
    int mid = (l + r) / 2;
    pair<long long, long long> best = {INF, optl};
    for (int i = optl; i <= optr && i < mid; ++i) {
        best = min(best, {cost[parts-1][i] + (long long)(p[mid]-p[i])*(p[mid]-p[i]), i});
    }
    cost[parts][mid] = best.first;
    int opt = best.second;
    solve(parts, l, mid-1, optl, opt);
    solve(parts, mid+1, r, opt, optr);
}

int main() {
    int n, k; cin >> n >> k;
    a = p = vector<int>(1+n);
    for (int i = 1; i <= n; ++i) cin >> a[i], p[i] = p[i-1] + a[i];
    cost.assign(1+k, vector<long long>(1+n, INF));
    cost[0][0] = 0;
    for (int i = 1; i <= k; ++i) solve(i, 1, n, 0, n-1);
    cout << cost[k][n] << endl;
    return 0;
}

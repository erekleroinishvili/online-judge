#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int const N = 5e5, A = 1e3;

// Fenwick Tree:
void update(vector<long long> &fenwick, int index, long long value) {
    while (index < (int)fenwick.size()) {
        fenwick[index] += value;
        index += index & -index;
    }
}
long long getSum(const vector<long long> &fenwick, int index) {
    long long sum = 0;
    while (index) {
        sum += fenwick[index];
        index -= index & -index;
    }
    return sum;
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, k, L, R;
    cin >> n >> k >> L >> R;
    vector<int> a(1+n), p(1+n);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i], p[i] = p[i-1] + a[i];
    }

    // compress values
    vector<int> decompress = p;
    sort(decompress.begin(), decompress.end());
    decompress.resize(unique(decompress.begin(), decompress.end()) - decompress.begin());
    decompress.insert(decompress.begin(), INT_MIN);
    int m = decompress.size();
    auto compress = [&decompress](int x) {
        return lower_bound(decompress.begin(), decompress.end(), x) - decompress.begin();
    };
    for (int &x : p) x = compress(x);
    // p[i] is now the compressed value, decompress[p[i]] is the initial value

    // binary search to find smallest loveliness in the composition
    int left = N*(-A), right = N*A+1;
    while (left+1 < right) {
        int mid = (left + right) / 2;
        
        // find how many chords have loveliness >= mid
        long long sufficientlyLovely = 0;
        vector<long long> fenwick(1+m); // indexed by compressed value of prefix sum
        for (int r = 1; r <= n && sufficientlyLovely < k; ++r) { // fix right endpoint of chord
            // chord cannot be longer than R - remove left endpoint
            if (r-R-1 >= 0) update(fenwick, p[r-R-1], -1);
            // chord can be of length L - add new left endpoint
            if (r-L >= 0) update(fenwick, p[r-L], +1);

            // decompress[p[r]] - decompress[p[l]] >= mid (l is the index before left endpoint)
            // r-R <= l <= r-L
            int maxPrefixSum = decompress[p[r]] - mid;
            int maxIndex = compress(maxPrefixSum+1)-1;
            sufficientlyLovely += getSum(fenwick, maxIndex);
        }

        // check if there are >= k values with loveliness >= mid
        if (sufficientlyLovely >= k) left = mid;
        else right = mid;
    }

    int minLoveliness = left;

    // find how many chords have loveliness >= minLoveliness, and find their sum
    long long sufficientlyLovelyCnt = 0, sufficientlyLovelySum = 0;
    vector<long long> fenwickCnt(1+m); // indexed by compressed value of prefix sum
    vector<long long> fenwickSum(1+m); // sums over leftpoint prefix sums
    for (int r = 1; r <= n; ++r) { // fix right endpoint of chord
        // chord cannot be longer than R - remove left endpoint
        if (r-R-1 >= 0) {
            update(fenwickCnt, p[r-R-1], -1);
            update(fenwickSum, p[r-R-1], -decompress[p[r-R-1]]);
        }
        // chord can be of length L - add new left endpoint
        if (r-L >= 0) {
            update(fenwickCnt, p[r-L], +1);
            update(fenwickSum, p[r-L], +decompress[p[r-L]]);
        }

        // decompress[p[r]] - decompress[p[l]] >= minLoveliness (l is the index before left endpoint)
        // r-R <= l <= r-L
        int maxPrefixSum = decompress[p[r]] - minLoveliness;
        int maxIndex = compress(maxPrefixSum+1)-1;
        long long curCnt = getSum(fenwickCnt, maxIndex);
        sufficientlyLovelyCnt += curCnt;
        long long curSum = curCnt*decompress[p[r]] - getSum(fenwickSum, maxIndex);
        sufficientlyLovelySum += curSum;
    }

    long long ans = sufficientlyLovelySum - (sufficientlyLovelyCnt-k)*minLoveliness;
    cout << ans << endl;
    return 0;
}

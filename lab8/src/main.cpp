#include <bits/stdc++.h>

#define ll long long

struct Interval {
    ll left;
    ll right;
    ll index;
};

bool compareIntervalsLeft(const Interval &a, const Interval &b) {
    return a.left < b.left;
}

bool compareIntervalsIndex(const Interval &a, const Interval &b) {
    return a.index < b.index;
}

int main() {
    ll n, m;
    std::cin >> n;
    std::vector<Interval> intervals(n);
    for (ll i = 0; i < n; ++i) {
        std::cin >> intervals[i].left >> intervals[i].right;
        intervals[i].index = i;
    }
    std::sort(intervals.begin(), intervals.end(), compareIntervalsLeft);

    std::vector<Interval> result;
    std::cin >> m;
    ll cover = 0, index = 0;
    while(cover < m) {
        ll max_Ri = cover;
        ll max_index = -1;
        while (index < n && intervals[index].left <= cover) {
            if (intervals[index].right > max_Ri) {
                max_Ri = intervals[index].right;
                max_index = index;
            }
            ++index;
        }
        if (max_index != -1) {
            result.push_back(intervals[max_index]);
            cover = max_Ri;
        } else {
            break;
        }
    }

    if (cover < m) {
        result.clear();
    }
    std::cout << result.size() << '\n';
    std::sort(result.begin(), result.end(), compareIntervalsIndex);
    for (const auto& elem : result) {
        std::cout << elem.left << ' ' << elem.right << '\n';
    }

    return 0;
}
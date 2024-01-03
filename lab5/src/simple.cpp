#include <bits/stdc++.h>

using namespace std;

vector<int> Find(string text, string pattern) {
    vector<int> result;
    for (size_t start = 0; start < text.size(); ++start) {
        bool flag = true;
        for (size_t j = 0; j < pattern.size(); ++j) {
            if (text[start+j] != pattern[j]) {
                flag = false;
                break;
            }
        }
        if (flag) {
            result.push_back((int)start);
        }
    }
    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    string text;
    cin >> text;
    // chrono::time_point<chrono::system_clock> start, end;
    // start = chrono::system_clock::now();
    long long word_number = 0;
    string pattern;
    while (cin >> pattern) {
        ++word_number;
        vector<int> result = Find(text, pattern);
       if (!result.empty()) {
           sort(result.begin(), result.end());
           cout << word_number << ": ";
           for (size_t i = 0; i < result.size(); ++i) {
               if (i > 0) {
                   cout << ", ";
               }
               cout << result[i] + 1;
           }
           cout << "\n";
       }
    }
    // end = chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds = end - start;
    // cout << "Simple: количество паттернов - " << word_number << " Время - " << elapsed_seconds.count() << "\n";
    return 0;
}
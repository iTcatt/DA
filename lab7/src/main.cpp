#include <bits/stdc++.h>

using namespace std;

void CleanStack(stack<int> &stack) {
    while (!stack.empty()) {
        stack.pop();
    }
}

int main() {
//    ios_base::sync_with_stdio(false);
//    cin.tie(nullptr), cout.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> matrix(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        string row;
        cin >> row;
        for (int j = 0; j < m; ++j) {
            matrix[i][j] = row[j] - '0';
        }
    }
    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

    // в j ячейке хранится номер ближайшей сверху строки, в которой matrix[i][j]=1
    vector<int> ones_above(m, -1);
    // в j ячейке хранится ближайший слева столбец, который имеет меньше нулей сверху, чем у j
    vector<int> nearest_left(m);
    // в j ячейке хранится ближайший справа столбец, который имеет меньше нулей сверху, чем у j
    vector<int> nearest_right(m);

    stack<int> nearest_smaller_height;
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (matrix[i][j] == 1) {
                ones_above[j] = i;
            }
        }
        CleanStack(nearest_smaller_height);
        for(int j = 0; j < m; ++j) {
            while (nearest_smaller_height.size() != 0 && ones_above[nearest_smaller_height.top()] <= ones_above[j]) {
                nearest_smaller_height.pop();
            }
            if (nearest_smaller_height.size() > 0) {
                nearest_left[j] = nearest_smaller_height.top();
            } else {
                nearest_left[j] = -1;
            }
            nearest_smaller_height.push(j);
        }

        CleanStack(nearest_smaller_height);
        for (int j = m-1; j >= 0; --j) {
            while (nearest_smaller_height.size() != 0 && ones_above[nearest_smaller_height.top()] <= ones_above[j]) {
                nearest_smaller_height.pop();
            }
            if (nearest_smaller_height.size() > 0) {
                nearest_right[j] = nearest_smaller_height.top();
            } else {
                nearest_right[j] = m;
            }
            nearest_smaller_height.push(j);
        }

        for (int j = 0; j < m; ++j) {
            long long current_square = (i - ones_above[j]) * (nearest_right[j] - nearest_left[j] - 1);
            if (current_square > result) {
                result = current_square;

        }

    }
//    cout << result << '\n';
    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "Строк - "  << n << " Столбцов - " << m << " Время - " << elapsed_seconds.count() << "\n";
    return 0;
}
#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<int> CountingSort(vector<int> input, int radix) {
    int counter[10];
    for (int i = 0; i < 10; i++) {
        counter[i] = 0;
    }
    for (int i = 0; i < input.size(); ++i) {
        counter[input[i] / (int(pow(10, radix))) % 10] += 1;
    }
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    vector<int> result(input.size());
    for (int i = input.size() - 1; i >= 0; --i) {
        result[counter[input[i] % 10] - 1] = input[i];
        counter[input[i] % 10] -= 1;
    }
    return result;
}


int main() {
    int tmp;
    vector<int> input;
    while (cin >> tmp) {
        input.push_back(tmp);
    }
    int maxRadix = -1;
    for (int i = 0; i < input.size(); ++i) {
        tmp = input[i];
        int current = 0; 
        while (tmp > 0) {
            ++current;
            tmp /= 10;
        }
        maxRadix = max(current, maxRadix);
    }

    for (int i = 0; i < maxRadix; ++i) {
        input = CountingSort(input, i);
    }

    for (int i = 0; i < input.size(); ++i) {
        cout << input[i] << ' ';
    }
    cout << '\n';
    return 0;
}
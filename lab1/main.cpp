
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

void CountingSort(vector<int> &input, int radix) {
    int counter[10];
    for (int i = 0; i < 10; ++i) {
        counter[i] = 0;
    }
   
    int r = pow(10, radix);
    for (int i = 0; i < input.size(); ++i) {
        counter[(input[i] / r) % 10] += 1;
    }
    
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    vector<int> result(input.size());
    copy(input.begin(), input.end(), result.begin());
   
    for (int i = input.size() - 1; i >= 0; --i) {
        input[counter[result[i] / r % 10] - 1] = result[i];
        counter[result[i] / r % 10] -= 1;
    }

}

void RadixSort(vector<int> &input, int max_radix) {
    for (int i = 0; i < max_radix; ++i) {
        CountingSort(input, i);
    }
}

int main() {
    int tmp;
    vector<int> input;
    while (cin >> tmp) {
        input.push_back(tmp);
    }
    // тестовый массив, для проверки сортировки
    vector<int> test(input.size());
    copy(input.begin(), input.end(), test.begin());  
    // ------------------------------------------------
    int max_radix = -1;
    for (int i = 0; i < input.size(); ++i) {
        tmp = input[i];
        int current = 0; 
        while (tmp > 0) {
            ++current;
            tmp /= 10;
        }
        max_radix = max(current, max_radix);
    }
    
    cout << "my result\n";
    for (int i = 0; i < input.size(); ++i) {
        cout << input[i] << ' ';
    }
    cout << "\n\n";
    sort(test.begin(), test.end());
    for (auto elem : test) {
        cout << elem << " ";
    }
    cout << "\n";
    return 0;
}
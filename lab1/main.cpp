
#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>

using namespace std;

struct Node {
    unsigned long long key;
    string value;
};

void CountingSort(vector<Node> &input, int radix) {
    int counter[10];
    for (int i = 0; i < 10; ++i) {
        counter[i] = 0;
    }
   
    unsigned long long r = pow(10, radix);
    for (int i = 0; i < input.size(); ++i) {
        counter[(input[i].key / r) % 10] += 1;
    }
    
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    vector<Node> helper(input.size());
    copy(input.begin(), input.end(), helper.begin());
   
    for (int i = input.size() - 1; i >= 0; --i) {
        input[counter[helper[i].key / r % 10] - 1] = helper[i];
        counter[helper[i].key / r % 10] -= 1;
    }

}

void RadixSort(vector<Node> &input, int max_radix) {
    for (int i = 0; i < max_radix; ++i) {
        CountingSort(input, i);
    }
}

bool cmp(Node first, Node second) {
    return first.key < second.key;
}

int main() {
    unsigned long long key;
    string value;
    vector<Node> input;
    while (cin >> key >> value) {
        Node tmp = {key, value};
        input.push_back(tmp);
    }
    // тестовый массив, для проверки сортировки
    vector<Node> test(input.size());
    copy(input.begin(), input.end(), test.begin());  
    // ------------------------------------------------
    int max_radix = -1;
    for (int i = 0; i < input.size(); ++i) {
        unsigned long long tmp = input[i].key;
        int current = 0; 
        while (tmp > 0) {
            ++current;
            tmp /= 10;
        }
        max_radix = max(current, max_radix);
    }
    RadixSort(input, max_radix);
    cout << "my result\n";
    for (int i = 0; i < input.size(); ++i) {
        cout << input[i].key << " " << input[i].value << "\n";
    }
    cout << "\n\n";
    sort(test.begin(), test.end(), cmp);
    for (auto elem : test) {
        cout << elem.key << " " << elem.value << "\n";
    }
    cout << "\n";
    return 0;
}
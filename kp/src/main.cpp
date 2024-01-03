#include <bits/stdc++.h>

using namespace std;

bool cmp(const pair<int, const char*>& lhs, const pair<int, const char*>& rhs) {
    return strcmp(lhs.second, rhs.second) <= 0;
}

string BurrowsWheelerTransform(const string& text) {
    vector<pair<int, const char*>> suffixes(text.size());
    for (int i = 0; i < text.size(); ++i) {
        suffixes[i].first = i;
        suffixes[i].second = &text[i];
    }
    sort(suffixes.begin(), suffixes.end(), cmp);

    string result(text.size(), ' ');
    for (int i = 0; i < text.size(); ++i) {
        int j = (suffixes[i].first + suffixes.size() - 1) % suffixes.size();
        result[i] = text[j];
    }
    return result;
}

vector<int> MoveToFront(const string& text) {
    vector<int> result(text.size());
    string alphabet = "$abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < text.size(); ++i) {
        int index = 0;
        while (alphabet[index] != text[i]) {
            ++index;
        }
        result[i] = index;
        if (index != 0) {
            alphabet.erase(alphabet.begin() + index);
            alphabet = text[i] + alphabet;
        }
    }
    return result;
}

vector<pair<int, int>> RunLengthEncoding(const vector<int>& text) {
    vector<pair<int, int>> result;
    result.reserve(text.size());
    int prev = -1;
    int counter = 1;
    for (auto ch : text) {
        if (prev != ch) {
            if (counter > 1) {
                result[result.size()-1].first = counter;
                counter = 1;
            }
                result.emplace_back(1, ch);
        } else {
            ++counter;
        }
        prev = ch;
    }
    if (counter > 1) {
        result[result.size()-1].first = counter;
    }
    return result;
}

vector<int> ReverseRunLengthEncoding(const vector<pair<int, int>>& codes) {
    int length = 0;
    for (auto elem : codes) {
        length += elem.first;
    }
    vector<int> result(length);
    int index = 0;
    for (auto elem : codes) {
        for (int shift = 0; shift < elem.first; ++shift) {
            result[index + shift] = elem.second;
        }
        index += elem.first;
    }
    return result;
}

string ReverseMoveToFront(const vector<int>& text) {
    string result;
    result.reserve(text.size());
    string alphabet = "$abcdefghijklmnopqrstuvwxyz";
    for (auto index : text) {
        result.push_back(alphabet[index]);
        if (index != 0) {
            char ch = alphabet[index];
            alphabet.erase(alphabet.begin() + index);
            alphabet = ch + alphabet;
        }
    }
    return result;
}

string ReverseBurrowsWheelerTransform(const string& encoded) {
    vector<int> first(encoded.size()); // первый преподсчет, считаем для каждого символа строки сдвигов, количество символов на подтроке до него, которые равны ему
    unordered_map<char, int> count(27);
    for (int pos = 0; pos < encoded.size(); ++pos) {
        if (count.find(encoded[pos]) == count.end()) {
            count[encoded[pos]] = 1;
        } else {
            ++count[encoded[pos]];
        }
        first[pos] = count[encoded[pos]] - 1;
    }
    unordered_map<char, int> second(27); // второй преподсчет, мы для каждого символа строки сдвигов будем считать кол-во символов, лексикографически меньших чем текущий
    second['$'] = 0;
    int prev = 1;
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        if (count.find(ch-1) != count.end()) {
            second[ch] = second[ch-1] + count[ch-1];
        } else {
            second[ch] = prev;
        }
        prev = second[ch];
    }
    int index = 0;
    while (encoded[index] != '$') {
        ++index;
    }
    string result(encoded.size(), '$');
    for (int position = encoded.size()-2; position >= 0; --position) {
        index = first[index] + second[encoded[index]];
        result[position] = encoded[index];
    }
    return result;
}

int main() {
    string type;
    cin >> type;
    if (type == "compress") {
        string text;
        cin >> text;
        string step_one = BurrowsWheelerTransform(text + "$");
        vector<int> step_two = MoveToFront(step_one);
        vector<pair<int, int>> step_three = RunLengthEncoding(step_two);
        for (auto elem : step_three) {
            cout << elem.first << " " << elem.second << endl;
        }
    } else if (type == "decompress") {
        vector<pair<int, int>> codes;
        pair<int, int> current;
        while (cin >> current.first >> current.second) {
            codes.push_back(current);
        }
        vector<int> step_one = ReverseRunLengthEncoding(codes);
        string step_two = ReverseMoveToFront(step_one);
        string step_three = ReverseBurrowsWheelerTransform(step_two);
        step_three.erase(step_three.begin() + step_three.size() - 1);
        cout << step_three << endl;
    } else {
        return -1;
    }
    return 0;
}

#include <iostream>
#include <string>
#include <string.h>
#include <map>
#include <chrono>

using namespace std;

const short MAX_SIZE = 257;

void TolowerString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    chrono::time_point<std::chrono::steady_clock> start;
    chrono::time_point<std::chrono::steady_clock> end;
    double time;

    map <string, unsigned long long> dict;
    char buffer[MAX_SIZE];
    char key[MAX_SIZE];
    string lol;
    unsigned long long value;
    map <string, unsigned long long> :: iterator it, result;
    start = std::chrono::steady_clock::now();
    while(cin >> buffer) {
        switch (buffer[0]) {
            case '+':
                cin >> key >> value;
                TolowerString(key);
                lol = key;
                dict.insert(make_pair(lol, value));
                break;
            case '-':
                cin >> buffer;
                TolowerString(buffer);
                result = dict.find(buffer);
                dict.erase(buffer);
                break;
            case '#':
                end = std::chrono::steady_clock::now();
                time = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
                cout << "Time: " << time << "\n";
                start = end;
                break;
            default:
                TolowerString(buffer);
                result = dict.find(buffer);
                break;  
        }
    }
    return 0;
}
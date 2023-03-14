#include <iostream>
#include <string>
#include "binary-tree.h"

using namespace std;

int main() {
    int command = 0;
    int key;
    Tree tree;
    while (command != 4) {
        cout << "1) Init\n2) Insert\n3) Print\n4) Exit\nВведите команду: ";
        std::cin >> command;
        switch (command) {
        case 1:
            cout << "Введите число: ";
            cin >> key;
            tree.init(key);
            break;
        case 2:
            cout << "Введите число: ";
            cin >> key;
            if (tree.insert(key)) {
                cout << "OK\n";
            } else {
                cout << "Already\n";
            }
            break;
        case 4:
            break;
        default:
            cout << "I don't know this command\n";
            break;
        }
    }

    return 0;
}
#include <iostream>
#include <string.h>

using namespace std;

struct Node {

};


class BTree {
    Node root;
    int t;
public:
    void AddNode(char* key, unsigned long long value);
    void DeleteNode(char* key);
    void FindValue(char* key);
    void Save(char* path);
    void Load(char* path);
    void Print();
};

void BTree::AddNode(char* key, unsigned long long value) {
    cout << "I am read " << key << " " << value << "\n";
}

void BTree::DeleteNode(char* key) {
    cout << key << " was deleted\n";
}

void BTree::FindValue(char* key) {
    cout << "Find " << key << "\n";
}

void BTree::Save(char* path) {
    cout << "Save Tree in " << path << "\n";
}

void BTree::Load(char* path) {
    cout << "Load Tree in " << path << "\n";
}

void BTree::Print() {
    cout << "Lol\n";
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL); 
    // cout.tie(NULL);

    BTree Tree;
    char buffer[256];
    char key[256];
    char command[5];
    char path[256];
    unsigned long long value;

    while(cin >> buffer) {
        switch (buffer[0]) {
            case '+':
                cin >> key >> value;
                Tree.AddNode(key, value);
                break;
            case '-':
                cin >> key;
                Tree.DeleteNode(key);
                break;
            case '!':
                cin >> command >> path;
                if (!strcmp(command, "Save")) {
                    Tree.Save(path);
                } else {
                    Tree.Load(path);
                }
                break;
            case 'p':
                Tree.Print();
                break;
            default:
                Tree.FindValue(buffer);
                break;
        }
    }
    return 0;
}
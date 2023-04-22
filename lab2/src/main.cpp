#include <iostream>
#include <string.h>

using namespace std;

const short MAX_SIZE = 257;

struct Data {
    char key[MAX_SIZE];
    unsigned long long value;
};

struct Node {
    Data* data; // массив ключ-значение
    Node** child; // массив указателей на детей
    int n; // количество элементов
    bool leaf;
    int t;

    Node(int, bool);
    void Traverse(int); // функция вывода всех ключей текущего поддерева
    Node* Search(char*); // поиск ноды с нужным ключем
    void SplitChild(int, Node*);
    void InsertNonFull(Data);
    void Remove(char*);
    void RemoveFromLeaf(int);
    void RemoveFromNonLeaf(int);
    void Merge(int);
};

Node::Node(int _t, bool is_leaf) {
    t = _t;
    leaf = is_leaf;
    data = new Data[2 * t - 1];
    child = new Node*[2 * t];
    n = 0;
}

void Node:: Traverse(int depth) {
    for (int i = 0; i < n; i++) {
        if (leaf == false) {
            child[i]->Traverse(depth+1);
        }
        for (int j = 0; j < depth; ++j) {
            cout << "\t";
        } 
        cout << data[i].key << " " << data[i].value << "\n";
    }
    // обработка последнего ребенка
    if (leaf == false) {
        child[n]->Traverse(depth+1);
    }
}

Node* Node::Search(char* key) {
    int i = 0;
    while (i < n && strcmp(key, data[i].key) > 0) {
        i++;
    }

    if (strcmp(key, data[i].key) == 0) {
        return this;
    }

    if (leaf == true) {
        return nullptr;
    }
    return child[i]->Search(key);
}  

void Node::SplitChild(int i, Node* y) {
    // i это индекс, в который попадет ключ из дочернего узла
    // y это дочерний узел, который мы разделяем
    
    // создаем новый узел
    Node* z = new Node(y->t, y->leaf);
    z->n = t - 1;
    // копируем вторую половину старого узла в новый
    for (int j = 0; j < t - 1; ++j) {
        z->data[j] = y->data[j + t];
    }
    // если есть дети, то их тоже перепривязываем
    if (y->leaf == false) {
        for (int j = 0; j < t; ++j) {
            z->child[j] = y->child[j+t];
        }
    }
    
    y->n = t - 1;

    for (int j = n; j >= i + 1; --j) {
        child[j + 1] = child[j];
    }
    // теперь z стал правым ребенком, а y стал левым 
    child[i + 1] = z;
    // сдвигаю ключи вправо, чтобы поставить новый ключ
    for (int j = n - 1; j >= i; --j) {
        data[j + 1] = data[j];
    }
    // ставим в родительский узел середину дочернего узла
    data[i] = y->data[t - 1];
    ++n;
}

void Node::InsertNonFull(Data elem) {
    int i = n - 1;

    if (leaf == true) {
        while (i >= 0 && strcmp(data[i].key, elem.key) > 0) {
            data[i+1] = data[i];
            --i;
        }
        data[i + 1] = elem;
        ++n;
    } else {
        while (i >= 0 && strcmp(data[i].key, elem.key) > 0) {
            --i;
        }
        // если ребенок заполнен
        if (child[i+1]->n == 2*t-1) {
            this->SplitChild(i + 1, child[i+1]);

            if (strcmp(elem.key, data[i+1].key) > 0) {
                ++i;
            }
        }
        child[i+1]->InsertNonFull(elem);
    }
}

void Node::Remove(char* key) {
    int idx = 0;
    while (idx < n && strcmp(key, data[idx].key) > 0) {
        ++idx;
    }

    if (idx < n && strcmp(key, data[idx].key) == 0) {
        if (leaf) {
            RemoveFromLeaf(idx);
        } else {
            RemoveFromNonLeaf(idx); 
        }
    } else {

    }
}

void Node::RemoveFromLeaf(int index) {
    for (int i = index+1; i < n; i++) {
        data[i-1] = data[i];
    }
    --n;
}

void Node::RemoveFromNonLeaf(int index) {
    cout << index;
}

void Node::Merge(int index) {
    Node* left_child = child[index];
    Node* right_child = child[index+1];

    // спускаем родителя вниз
    left_child->data[t-1] = data[index];
    // копируем значения
    for (int i = 0; i < t - 1; ++i) {
        left_child->data[i+t] = right_child->data[i]; 
    }
    // копируем детей
    if (!left_child->leaf) {
        for (int i = 0; i < t; ++i) {
            left_child->child[i + t] = right_child->child[i];
        }
    }
    // так как мы спустили родителя, то смещаем все ключи родильского узла влево
    for (int i = index + 1; i < n; ++i) {
        data[i-1] = data[i];
    }

    for (int i = index + 2; i < n; ++i) {
        child[i-1] = child[i];
    }

    left_child->n = 2*t - 1;
    --n;
    delete[] right_child;
}

class BTree {
    Node* root;
    int t;
public:
    BTree(int);
    void AddNode(Data);
    void DeleteNode(char*);
    void Search(char*);
    void SaveToFile(char*);
    void LoadFromFile(char*);
    void Print();
    // ~BTree();
};

BTree::BTree(int _t = 2) {
    root = nullptr;
    t = _t;
}

void BTree::AddNode(Data elem) {
    if (root == nullptr) {
        root = new Node(t, true);
        root->data[0] = elem;
        root->n = 1;
        cout << "OK\n";
        return;
    }
    // ключ уже есть
    if (root->Search(elem.key) != nullptr) {
        cout << "Exist\n";
        return;
    }
    // надо сплитануть корень
    if (root->n == 2*t-1) {
        Node* new_root = new Node(t, false);
        new_root->child[0] = root;
        new_root->SplitChild(0, root);
        // отвечает за то, в какое поддерево нужно вставлять ключ
        int i = 0;
        if (strcmp(elem.key, new_root->data[0].key) > 0) {
            ++i;
        }
        new_root->InsertNonFull(elem);
        root = new_root;
    } else { 
        root->InsertNonFull(elem);
    }
    cout << "OK\n";

}

void BTree::Search(char* key) {
    if (root == nullptr) {
        cout << "NoSuchWord\n";
        return;
    }

    Node* result = root->Search(key);
    if (result == nullptr) {
        cout << "NoSuchWord\n";
    } else {
        int i = 0;
        while (i < result->n && strcmp(key, result->data[i].key) > 0) {
            i++;
        }
        cout << "OK: " << result->data[i].value << "\n";
    }

}

void BTree::DeleteNode(char* key) {
    if (root == nullptr) {
        cout << "NoSuchWord\n";
        return;
    }
    
    if (root->Search(key) == nullptr) {
        cout << "NoSuchWord\n";
        return;
    }



    
}

void BTree::SaveToFile(char* path) {
    cout << "Save To File Tree in " << path << "\n";
}

void BTree::LoadFromFile(char* path) {
    cout << "Load Tree from" << path << "\n";
}

void BTree::Print() {
    if (root != nullptr) {
        root->Traverse(0);
    } else {
        cout << "Emtpy\n";
    }
}

void TolowerString(char* str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL); 
    // cout.tie(NULL);

    BTree Tree(3);
    char key[MAX_SIZE];
    char path[MAX_SIZE];
    char buffer[MAX_SIZE];
    while(cin >> buffer) {
        switch (buffer[0]) {
            case '+':
                Data data;
                cin >> data.key >> data.value;
                TolowerString(data.key);
                Tree.AddNode(data);
                break;
            case '-':
                cin >> key;
                TolowerString(data.key);
                Tree.DeleteNode(key);
                break;
            case '!':
                cin >> buffer >> path;
                if (!strcmp(buffer, "Save")) {
                    Tree.SaveToFile(path);
                } else {
                    Tree.LoadFromFile(path);
                }
                break;
            case 'p':
                Tree.Print();
                break;
            default:
                TolowerString(buffer);
                Tree.Search(buffer);
                break;
        }
    }
    return 0;
}
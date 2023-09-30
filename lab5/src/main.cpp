#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

string build_string;

struct Node {
    int start;
    int end;
    int position;
    vector<Node*> next;

    Node(int, int, int);
    ~Node();
    void Insert(int, int);
    vector<int> Find(string);
    void AllPositions(vector<int> &);
    void Print(int);
};

Node::Node(int start, int end, int position) {
    this->start = start;
    this->end = end;
    this->position = position;
    this->next.resize(27); // 26 букв + 1 терминал
}

Node::~Node() {
    for (auto child: next) {
        delete child;
    }
}

void Node::Insert(int begin, int stance) {
    if (next[build_string[begin] - 'a'] == nullptr) {
        next[build_string[begin] - 'a'] = new Node(begin, (int)build_string.length() - 1, stance);
        return;
    }
    Node* current = next[build_string[begin] - 'a'];
    int match_shift = 0;
    while (current->start + match_shift <= current->end) {
        if (build_string[begin + match_shift] != build_string[current->start + match_shift]) {
            break;
        }
        ++match_shift;
    }
    // split node
    if (current->start + match_shift <= current->end) {
        Node* new_node = new Node(current->start, current->start + match_shift - 1, -1);
        current->start += match_shift;
        new_node->next[build_string[current->start] - 'a'] = current;
        new_node->next[build_string[begin + match_shift] - 'a'] = new Node(
                begin + match_shift,
                (int)build_string.length() - 1,
                stance
                );
        next[build_string[begin] - 'a'] = new_node;
    } else {
        current->Insert(begin + match_shift, stance);
    }
}

vector<int> Node::Find(string pattern) {
    bool is_contain = true;
    Node* current = this;
    size_t last_matched = 0;
    while(last_matched < pattern.size()) {
        current = current->next[pattern[last_matched] - 'a'];
        if (current == nullptr) {
            is_contain = false;
            break;
        }
        for (int i = current->start; i <= current->end && last_matched < pattern.size(); ++i) {
            if (pattern[last_matched] != build_string[i]) {
                break;
            }
            ++last_matched;
        }

        if (last_matched < pattern.size() && current->start + (int)last_matched <= current->end) {
            is_contain = false;
            break;
        }
    }
    vector<int> entrances;
    if (is_contain) {
        current->AllPositions(entrances);
    }
    return entrances;
}

void Node::AllPositions(vector<int> &entrances) {
    if (position != -1) {
        entrances.push_back(position);
        return;
    }

    for (int i = 0; i < 27; ++i) {
        if (next[i] != nullptr) {
            next[i]->AllPositions(entrances);
        }
    }
}

void Node::Print(int depth) {
    if (depth != 0) {
        for (int i = 0; i < depth - 1; ++i) {
            cout << "\t";
        }
        cout << start << " "
             << end << " "
             << build_string.substr(start, end - start + 1) << "\t"
             << position << "\n";
    }
    for (int i = 0; i < 27; ++i) {
        Node* current = next[i];
        if (current != nullptr) {
            current->Print(depth + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr), cout.tie(nullptr);

    string text;
    cin >> text;
    build_string = text + "{";
    // chrono::time_point<chrono::system_clock> start, end;
    // start = chrono::system_clock::now();
    Node suffix_tree_root = Node(-1, -1, -1);
    for (size_t position = 0; position < build_string.length(); ++position) {
        suffix_tree_root.Insert((int)position, (int)position);
    }

    int word_number = 0;
    string pattern;
    while (cin >> pattern) {
        ++word_number;
        vector<int> entrances = suffix_tree_root.Find(pattern);
       if (!entrances.empty()) {
           sort(entrances.begin(), entrances.end());
           cout << word_number << ": ";
           for (size_t i = 0; i < entrances.size(); ++i) {
               if (i > 0) {
                   cout << ", ";
               }
               cout << entrances[i] + 1;
           }
           cout << "\n";
       }
    }
    // end = chrono::system_clock::now();
    // chrono::duration<double> elapsed_seconds = end - start;
    // cout << "Main: количество паттернов - " << word_number << " Время - " << elapsed_seconds.count() << "\n";
//    suffix_tree_root.Print(0);
    return 0;
}

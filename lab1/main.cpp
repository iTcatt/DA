
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <fstream>

using namespace std;

struct Node {
    unsigned long long key;
    char* value;
};

void CountingSort(Node* input, int size, int radix) {
    int counter[10];
    for (int i = 0; i < 10; ++i) {
        counter[i] = 0;
    }
   
    unsigned long long r = pow(10, radix);
    for (int i = 0; i < size; ++i) {
        counter[(input[i].key / r) % 10] += 1;
    }
    
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    Node* helper = new Node[size];
    for (int i = 0; i < size; ++i) {
        helper[i] = input[i];
    }
   
    for (int i = size - 1; i >= 0; --i) {
        input[counter[helper[i].key / r % 10] - 1] = helper[i];
        counter[helper[i].key / r % 10] -= 1;
    }
    delete[] helper;

}

void RadixSort(Node* input, int size, int max_radix) {
    for (int i = 0; i < max_radix; ++i) {
        CountingSort(input, size, i);
    }
}

int FindMaxDischarge(Node* input, int size) {
    int max_radix = -1;
    for (int i = 0; i < size; ++i) {
        unsigned long long tmp = input[i].key;
        int current = 0; 
        while (tmp > 0) {
            ++current;
            tmp /= 10;
        }
        max_radix = max(current, max_radix);
    }
    return max_radix;
}

int main() {
    int size = 0;
    int capacity = 1;
    Node* array = new Node[capacity];

    unsigned long long key;  
    char* buffer = new char[2049];
    for (int i = 0; i < 2048; ++i) {
        buffer[i] = '#';
    }
    while (scanf("%llu\t%s", &key, buffer) != EOF) {
        int string_size = 0;
        while (buffer[string_size] != '#' && string_size < 2048) {
            ++string_size;
        }
        char* str = new char[string_size];
        for (int i = 0; i < string_size; ++i) {
            str[i] = buffer[i];
        }
        if (size == capacity) {
            Node* tmp = array;
            array = new Node[capacity * 2];
            for (int i = 0; i < capacity; ++i) {
                array[i] = tmp[i];
            }
            capacity *= 2;
            delete[] tmp;
        }
        array[size] = {key, str};
        ++size;
        for (int i = 0; i < 2048; ++i) {
            buffer[i] = '#';
        }
    }
    delete buffer;
    int max_radix = FindMaxDischarge(array, size);
    RadixSort(array, size, max_radix);
    for (int i = 0; i < size; ++i) {
        printf("%llu\t%s\n", array[i].key, array[i].value);
    }
    delete[] array;

    return 0;
}
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Node {
    unsigned long long key;
    char* value;
};

void CountingSort(Node* array, int size, int radix) {
    int counter[10] = {0};
    unsigned long long r = std::pow(10, radix);
    
    for (int i = 0; i < size; ++i) {
        counter[(array[i].key / r) % 10] += 1;
    }
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    Node* helper = new Node[size];
    for (int i = 0; i < size; ++i) {
        helper[i] = array[i];
    }
   
    for (int i = size - 1; i >= 0; --i) {
        array[counter[helper[i].key / r % 10] - 1] = helper[i];
        counter[helper[i].key / r % 10] -= 1;
    }
    delete[] helper;
}

void RadixSort(Node* array, int size, int max_radix) {
    for (int i = 0; i < max_radix; ++i) {
        CountingSort(array, size, i);
    }
}

int FindMaxDischarge(Node* array, int size) {
    int max_radix = -1;
    for (int i = 0; i < size; ++i) {
        unsigned long long number = array[i].key;
        int current = 0; 
        while (number > 0) {
            ++current;
            number /= 10;
        }
        max_radix = std::max(current, max_radix);
    }
    return max_radix;
}

int main() {
    int size = 0;
    int capacity = 1;
    Node* array = new Node[capacity];
    FILE* input = fopen("input.txt", "r");
    unsigned long long key;  
    char buffer[2048];
    while (fscanf(input, "%llu\t%s", &key, buffer) != EOF) {
        char* str = new char[strlen(buffer) + 1];
        for (int i = 0; i < strlen(buffer); ++i) {
            str[i] = buffer[i];
        }
        str[strlen(buffer)] = '\0';
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
    }
    int max_radix = FindMaxDischarge(array, size);
    RadixSort(array, size, max_radix);
    for (int i = 0; i < size; ++i) {
        printf("%llu\t%s\n", array[i].key, array[i].value);
        delete[] array[i].value;
    }
    
    delete[] array;
    return 0;
}

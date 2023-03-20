#include <iostream>
#include <stdio.h>
#include <chrono>
#include <algorithm>
#include <string.h>
#include <math.h>

struct Data {
    unsigned long long key;
    char* value;
};

class Vector {
private:
    Data* array;
    int size;
    int capacity;
public:
    Vector() {
        capacity = 1;
        size = 0;
        array = new Data[capacity];
    }
    
    Data* begin() {
		return &array[0];
    }

    Data* end() {
        return &array[size-1];
    }

    void ReadFromFile(char* file_name) {
        FILE* input = fopen(file_name, "r");
        unsigned long long key;  
        char buffer[2048];
        while (fscanf(input, "%llu\t%s", &key, buffer) != EOF) {
            char* str = new char[strlen(buffer) + 1];
            for (int i = 0; i < strlen(buffer); ++i) {
                str[i] = buffer[i];
            }
            str[strlen(buffer)] = '\0';
            if (size == capacity) {
                AddMemory();
            }
            array[size] = {key, str};
            ++size;
        }
        fclose(input);
    }
    
    void AddMemory() {
        Data* tmp = array;
        array = new Data[capacity * 2];
        for (int i = 0; i < capacity; ++i) {
            array[i] = tmp[i];
        }
        capacity *= 2;
        delete[] tmp;
    }

    int GetMaxDischarge() {
        int max_discharge = -1;
        for (int i = 0; i < size; ++i) {
            unsigned long long number = array[i].key;
            int current = 0; 
            while (number > 0) {
                ++current;
                number /= 10;
            }
            max_discharge = std::max(current, max_discharge);
        }
        return max_discharge;
    }  

    void RadixSort() {
        int max_discharge = GetMaxDischarge();
        for (int discharge = 0; discharge < max_discharge; ++discharge) {
            CountingSort(discharge);
        }
    }

    void CountingSort(int discharge) {
        int counter[10] = {0};
        unsigned long long ten_power_discharge = std::pow(10, discharge);
        
        for (int i = 0; i < size; ++i) {
            counter[(array[i].key / ten_power_discharge) % 10] += 1;
        }
        for (int i = 1; i < 10; ++i) {
            counter[i] += counter[i-1];
        }

        Data* copy_array = new Data[size];
        for (int i = 0; i < size; ++i) {
            copy_array[i] = array[i];
        }
    
        for (int i = size - 1; i >= 0; --i) {
            int discharge_digit = copy_array[i].key / ten_power_discharge % 10;
            array[counter[discharge_digit] - 1] = copy_array[i];
            counter[discharge_digit] -= 1;
        }
        delete[] copy_array;
    }

    void Print() {
        for (int i = 0; i < size; ++i) {
            printf("%llu\t%s\n", array[i].key, array[i].value);
        }   
    }

    ~Vector() {
        for (int i = 0; i < size; ++i) {
            delete[] array[i].value;
        }   
        delete[] array;
    }

    void BubbleSort() {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i].key < array[j].key) {
                    std::swap(array[i], array[j]);
                }
            }
        }
    }

};

bool cmp(Data first, Data second) {
    return first.key < second.key;
}

int main() {
    Vector data_array;
    char input_file[] = "test.txt";
    data_array.ReadFromFile(input_file);
    // auto start = std::chrono::high_resolution_clock::now();
    // std::sort(data_array.begin(), data_array.end(), cmp);
    data_array.RadixSort();
    // data_array.BubbleSort();
    // auto stop = std::chrono::high_resolution_clock::now();
    // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    // std::cout << "Time Bubble sort: " << duration.count() << " microseconds" << "\n";
    data_array.Print();
    return 0;
}

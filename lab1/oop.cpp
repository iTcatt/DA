#include <iostream>
#include <stdio.h>
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

    int getSize() {
        return size;
    }

    int getCapacity() {
        return capacity;
    }

    void readFromFile(char* file_name) {
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
                addMemory();
            }
            array[size] = {key, str};
            ++size;
        }
        fclose(input);
    }
    
    void addMemory() {
        Data* tmp = array;
        array = new Data[capacity * 2];
        for (int i = 0; i < capacity; ++i) {
            array[i] = tmp[i];
        }
        capacity *= 2;
        delete[] tmp;
    }

    int getMaxDischarge() {
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

    void radixSort(int max_discharge) {
        for (int discharge = 0; discharge < max_discharge; ++discharge) {
            countingSort(discharge);
        }
    }

    void countingSort(int discharge) {
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

    void printAndDeleteArray() {
        for (int i = 0; i < size; ++i) {
            printf("%llu\t%s\n", array[i].key, array[i].value);
            delete[] array[i].value;
        }   
        delete[] array;
    }

};

int main() {
    Vector data_array;
    char input_file[] = "input.txt";
    data_array.readFromFile(input_file);
    int max_discharge = data_array.getMaxDischarge();
    data_array.radixSort(max_discharge);
    data_array.printAndDeleteArray();
    return 0;
}

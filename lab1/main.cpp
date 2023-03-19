#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>

struct Data {
    unsigned long long key;
    char* string;
};

void CountingSort(Data* data_array, int array_size, int discharge) {
    int counter[10] = {0};
    unsigned long long ten_power_discharge = std::pow(10, discharge);
    
    for (int i = 0; i < array_size; ++i) {
        counter[(data_array[i].key / ten_power_discharge) % 10] += 1;
    }
    for (int i = 1; i < 10; ++i) {
        counter[i] += counter[i-1];
    }

    Data* copy_input_array = new Data[array_size];
    for (int i = 0; i < array_size; ++i) {
        copy_input_array[i] = data_array[i];
    }
   
    for (int i = array_size - 1; i >= 0; --i) {
        int discharge_digit = copy_input_array[i].key / ten_power_discharge % 10;
        data_array[counter[discharge_digit] - 1] = copy_input_array[i];
        counter[discharge_digit] -= 1;
    }
    delete[] copy_input_array;
}

void RadixSort(Data* data_array, int array_size, int max_discharge) {
    for (int discharge = 0; discharge < max_discharge; ++discharge) {
        CountingSort(data_array, array_size, discharge);
    }
}

int FindMaxDischarge(Data* data_array, int array_size) {
    int max_discharge = -1;
    for (int i = 0; i < array_size; ++i) {
        unsigned long long number = data_array[i].key;
        int current = 0; 
        while (number > 0) {
            ++current;
            number /= 10;
        }
        max_discharge = std::max(current, max_discharge);
    }
    return max_discharge;
}

Data* AddMemory(Data* data_array, int &array_capacity) {
    Data* tmp = data_array;
    data_array = new Data[array_capacity * 2];
    for (int i = 0; i < array_capacity; ++i) {
        data_array[i] = tmp[i];
    }
    array_capacity *= 2;
    delete[] tmp;
    return data_array;
}

void PrintAndDeleteArray(Data* data_array, int array_size) {
    for (int i = 0; i < array_size; ++i) {
        printf("%llu\t%s\n", data_array[i].key, data_array[i].string);
        delete[] data_array[i].string;
    }   
    delete[] data_array;
}

int main() {
    int array_size = 0;
    int array_capacity = 1;
    Data* data_array = new Data[array_capacity];
    FILE* input = fopen("input.txt", "r");
    unsigned long long key;  
    char buffer[2048];
    while (fscanf(input, "%llu\t%s", &key, buffer) != EOF) {
        char* str = new char[strlen(buffer) + 1];
        for (int i = 0; i < strlen(buffer); ++i) {
            str[i] = buffer[i];
        }
        str[strlen(buffer)] = '\0';
        if (array_size == array_capacity) {
            data_array = AddMemory(data_array, array_capacity);
        }
        data_array[array_size] = {key, str};
        ++array_size;
    }
    fclose(input);
    int max_discharge = FindMaxDischarge(data_array, array_size);
    RadixSort(data_array, array_size, max_discharge);
    PrintAndDeleteArray(data_array, array_size);
    return 0;
}

#include <iostream>
#include <stdio.h>
#include <string.h>

struct Data {
    unsigned long long key;
    char* value;
};

class Vector {
private:
    Data* array_;
    int size_;
    int capacity_;
public:
    Vector() {
        capacity_ = 1;
        size_ = 0;
        array_ = new Data[capacity_];
    }
    
    Data* begin() {
		return &array_[0];
    }

    Data* end() {
        return &array_[size_-1];
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
            if (size_ == capacity_) {
                AddMemory();
            }
            array_[size_] = {key, str};
            ++size_;
        }
        fclose(input);
    }
    
    void AddMemory() {
        Data* temp_array = array_;
        array_ = new Data[capacity_ * 2];
        for (int i = 0; i < capacity_; ++i) {
            array_[i] = temp_array[i];
        }
        capacity_ *= 2;
        delete[] temp_array;
    }

    void RadixSort() {
        for (int byte = 0; byte < 8; ++byte) {
            CountingSort(byte);
        }
    }

    void CountingSort(int byte) {
        int counter[256] = {0};
        for (int i = 0; i < size_; ++i) {
            counter[(array_[i].key >> byte * 8) & 255] += 1;
        }
        for (int i = 1; i < 256; ++i) {
            counter[i] += counter[i-1];
        }

        Data* copy_array = new Data[size_];
        for (int i = 0; i < size_; ++i) {
            copy_array[i] = array_[i];
        }

        for (int i = size_ - 1; i >= 0; --i) {
            int discharge_digit = (copy_array[i].key >> byte * 8) & 255;
            counter[discharge_digit] -= 1;
            array_[counter[discharge_digit]] = copy_array[i];
        }
        delete[] copy_array;
    }

    void Print() {
        for (int i = 0; i < size_; ++i) {
            printf("%llu\t%s\n", array_[i].key, array_[i].value);
        }   
    }

    ~Vector() {
        for (int i = 0; i < size_; ++i) {
            delete[] array_[i].value;
        }   
        delete[] array_;
    }
};

int main() {
    Vector data_array;
    char input_file[] = "input.txt";
    data_array.ReadFromFile(input_file);
    data_array.RadixSort();
    data_array.Print();
    return 0;
}

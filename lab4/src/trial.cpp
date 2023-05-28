#include <iostream>
#include <chrono>
#include <stdio.h>

using namespace std;

struct Data {
    int64_t value;
    int64_t string_number;
    int64_t word_number;
};

class Vector {
    Data* array_;
    uint64_t size_;
    uint64_t capacity_;

public:
    Vector(uint64_t capacity = 1) {
        capacity_ = capacity;
        size_ = 0;
        array_ = new Data[capacity_];
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

    void PushBack(Data elem) {
        if (size_ == capacity_) {
            AddMemory();
        }
        array_[size_] = elem;
        ++size_;
    }

    Vector& operator=(const Vector& right) {
        //проверка на самоприсваивание
        if (this == &right) {
            return *this;
        }
        array_ = right.array_;
        capacity_ = right.capacity_;
        size_ = right.size_;
        return *this;
    }

    Data& operator[](uint64_t index) {
        return array_[index];
    }

    uint64_t Length() {
        return size_;
    }

    uint64_t Capacity() {
        return capacity_;
    }

    ~Vector() {
        delete[] array_;
    }
};

void ScanPattern(Vector& pattern) {
    int64_t number;
    bool flag;
    char symbol = ' '; 
    while(symbol != '\n') {
        number = 0;
        flag = false;
        symbol = getchar();
        while (symbol != ' ' && symbol != '\n' && symbol != '\t' && symbol != '\r') {
            flag = true;
            number = number * 10 + (symbol - '0');
            symbol = getchar();
        }
        if (flag) {
            Data inserted_data = {number, 0, 0}; 
            pattern.PushBack(inserted_data);
        }
    }
}

void ScanText(Vector& text) {
    int64_t number;
    bool flag;
    int64_t string_number = 1, word_number = 1;
    char symbol = ' '; 
    while (symbol != EOF) {
        number = 0;
        flag = false;
        symbol = getchar();
        while (symbol != ' ' && symbol != '\n' && symbol != EOF && symbol != '\t' && symbol != '\r') {
            flag = true;
            number = number * 10 + (symbol - '0');
            symbol = getchar();
        }
        if (flag) {
            Data inserted_data = {number, string_number, word_number};
            text.PushBack(inserted_data);
            ++word_number;
        }

        if (symbol == '\n') {
            word_number = 1;
            ++string_number;
        }
    }
}

void Concatenation(Vector& pattern_and_text, Vector& pattern, Vector& text) {
    for (uint64_t i = 0; i < pattern.Length(); ++i) {
        pattern_and_text.PushBack(pattern[i]);
    }
    Data sentinel = {-1, -1, -1};
    pattern_and_text.PushBack(sentinel);
    for (uint64_t i = 0; i < text.Length(); ++i) {
        pattern_and_text.PushBack(text[i]);
    }
}

uint64_t min(uint64_t a, uint64_t b) {
    if (a > b) {
        return b;
    }
    return a;
} 

uint64_t* zFunction(Vector& input_string) {
    uint64_t string_size = input_string.Length();
    uint64_t* z_array = new uint64_t[string_size];
    for (int i = 0; i < string_size; ++i) {
        z_array[i] = 0;
    }
    
    uint64_t left = 0, right = 0; 
    for (uint64_t i = 1; i < string_size; ++i) {
        if (i <= right) {
            z_array[i] = min(z_array[i-left], z_array[right-i+1]);
        }
        while(i + z_array[i] < string_size && input_string[i + z_array[i]].value == input_string[z_array[i]].value) {
            ++z_array[i];
        }
        if (z_array[i] + i - 1 > right) {
            left = i;
            right = z_array[i] + i-1;
        }
    }
    return z_array;
}

uint64_t* zFunc(Vector& input_string) {
	int n = input_string.Length();
	uint64_t* z = new uint64_t[n];
    for (int i = 0; i < n; ++i) {
        z[i] = 0;
    }

	for (int i=1; i<n; ++i)
		while (i + z[i] < n && input_string[z[i]].value == input_string[i+z[i]].value)
			++z[i];
	return z;
}

void FindSubstrings(Vector& pattern_and_text, uint64_t* z_array, uint64_t len_pattern) {
    uint64_t index = 0;
    while (pattern_and_text[index].value != -1) {
        ++index;
    }
    for (int i = index+1; i < pattern_and_text.Length(); ++i) {
        if (z_array[i] == len_pattern) {
            cout << pattern_and_text[i].string_number << ", " << pattern_and_text[i].word_number << "\n"; 
        }
    }
}

int main() {
    Vector pattern, text;
    ScanPattern(pattern);
    ScanText(text);

    Vector pattern_and_text(pattern.Length() + text.Length() + 1);
    Concatenation(pattern_and_text, pattern, text); 

    uint64_t* z_array = zFunc(pattern_and_text);
    FindSubstrings(pattern_and_text, z_array, pattern.Length());

    delete[] z_array;
    return 0;
}
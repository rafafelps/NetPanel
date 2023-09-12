#pragma once

class Data {
public:
    unsigned int label;
    float* values;
    
    Data(unsigned int size) { values = new float[size]; }
    Data() { values = nullptr; }
    ~Data() { delete[] values; }
};

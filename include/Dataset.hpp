#pragma once
#include <string>
#include "Data.hpp"

class Dataset {
private:
    unsigned int width;
    unsigned int height;
    unsigned int size;

public:
    Data** data;

    Dataset(std::string pathL, std::string pathI);
    Dataset();
    ~Dataset();

    unsigned int getWidth() const;
    unsigned int getHeight() const;
    unsigned int getSize() const;

    void setData(std::string pathL, std::string pathI);
};

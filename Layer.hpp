#ifndef READER_HPP
#define READER_HPP

#include <iostream>
#include <math.h>
#include <vector>
#include <exception>

enum Matter
{
    ozon,
    oxigen,
    dioxid
};

class Layer
{
private:
    Matter name;
    double size;

public:
    Layer(char c, double size);

    Matter getName() const { return name; }

    double getSize() const { return size; }
    void setSize(const double size) { this->size = size; }

    std::string toString() const;
};

#endif // READER_HPP
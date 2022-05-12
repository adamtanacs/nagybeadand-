#ifndef ATMOSPHERE_HPP
#define ATMOSPHERE_HPP

#include "Layer.hpp"

#include <iostream>
#include <math.h>
#include <vector>
#include <exception>
#include <fstream>
#include <sstream>
#include <unistd.h>

class Atmosphere
{
private:
    std::ifstream f;
    std::vector<Layer> layers;
    std::string weather;

    void clearThins();

public:
    Atmosphere(const std::string path) : f(path)
    {
        if (!f)
        {
            throw new std::invalid_argument("File cannot be opened!");
        }
        int size;
        f >> size;
        for(int i = 0; i < size; i++)
        {
            char c; double lsize;
            f >> c >> lsize;
            Layer tmp(c,lsize);
            layers.push_back(tmp);
        }
        f >> weather;
        //weather = line;
    }

    bool createLayer(const Layer input, const unsigned int index);

    void upLayer(const Layer input, const unsigned int index);

    bool allElementsExits() const; //

    void simulate(); //

    void print(const unsigned int it); //

    int getSize() { return layers.size(); } //

    Layer getLayer(int index) 
    {
        if (index < getSize())
            return layers[index];
        else
            throw std::invalid_argument("Index out of bounds");
    }
};

#endif
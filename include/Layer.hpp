#pragma once

#include <iostream>
#include <vector>
#include "Neuron.hpp"

class Layer
{
private:
    int size;

    std::vector<Neuron *> neurons;

public:
    Layer(int size);
    ~Layer();
};

#pragma once

#include <iostream>
#include <vector>
#include "Neuron.hpp"
#include "Matrix.hpp"

class Layer
{
private:
    int size;

    std::vector<Neuron *> neurons;

public:
    Layer(std::vector<double> topology);
    Layer(int size);
    ~Layer();
    void setValue(uint index, double value);

    Matrix as_matrix(NeuronValueState state = Value, bool column_matrix = false);
};

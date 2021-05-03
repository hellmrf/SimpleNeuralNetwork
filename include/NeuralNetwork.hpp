#pragma once
#include <iostream>
#include <vector>
#include "Layer.hpp"
#include "Matrix.hpp"

class NeuralNetwork
{
private:
    std::vector<int> topology;
    std::vector<Layer> layers;
    std::vector<Matrix> weights;
    std::vector<double> inputLayer;

public:
    NeuralNetwork(std::vector<int> topology);
    ~NeuralNetwork();
    void setInputLayer(Layer input);
    Layer getLayer(uint index) const;
    std::vector<double> getOutputLayer();
    friend std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann);
};

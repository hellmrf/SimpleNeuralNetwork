#include <iostream>
#include <vector>
#include "Layer.hpp"
#include "Matrix.hpp"

class NeuralNetwork
{
private:
    std::vector<int> topology;
    std::vector<Layer *> layers;
    std::vector<Matrix *> weights;

public:
    NeuralNetwork(std::vector<int> topology);
    ~NeuralNetwork();
};

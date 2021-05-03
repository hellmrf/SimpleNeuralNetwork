#include "../include/NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(std::vector<int> topology)
{
    this->topology = topology;
    for (uint i = 0; i < this->topology.size(); ++i)
    {
        auto layer = Layer(this->topology[i]);
        this->layers.push_back(layer);
    }
    for (uint i = 0; i < this->topology.size() - 1; ++i)
    {
        auto m = Matrix(this->topology[i], this->topology[i + 1], true);
        this->weights.push_back(m);
    }
}

NeuralNetwork::~NeuralNetwork()
{
    this->layers.clear();
    this->weights.clear();
}

Layer NeuralNetwork::getLayer(uint index) const
{
    return this->layers.at(index);
}

void NeuralNetwork::setInputLayer(Layer layer)
{
}

std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann)
{
    bool begin = true;
    // for (auto layer : ann.layers)
    for (uint i = 0; i < ann.layers.size(); ++i)
    {
        if (begin)
        {
            os << "[1]  " << ann.getLayer(i).as_matrix(Value, false);
            begin = false;
        }
        else
        {
            os << "[" << i + 1 << "]  " << ann.getLayer(i).as_matrix(Activated, false);
        }
    }

    return os;
}
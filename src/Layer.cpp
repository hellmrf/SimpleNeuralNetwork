#include "../include/Layer.hpp"

Layer::Layer(int size)
{
    for (uint i = 0; i < size; ++i)
    {
        Neuron *n = new Neuron(0.00);
        this->neurons.push_back(n);
    }
}

Layer::~Layer()
{
    for (uint i = 0; i < neurons.size(); ++i)
    {
        delete neurons[i];
    }
}
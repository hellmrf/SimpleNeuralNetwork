#include "../include/Layer.hpp"

Layer::Layer(int size)
{
    this->size = size;
    for (uint i = 0; i < this->size; ++i)
    {
        auto n = Neuron(0.00);
        this->neurons.push_back(n);
    }
}
Layer::Layer(std::vector<double> layer)
{
    this->size = layer.size();
    for (uint i = 0; i < this->size; ++i)
    {
        auto n = Neuron(layer[i]);
        this->neurons.push_back(n);
    }
}

Layer::~Layer()
{
    this->neurons.clear();
}

void Layer::setValue(uint idx, double value)
{
    this->neurons.at(idx).setValue(value);
}

Matrix Layer::as_matrix(NeuronValueState state, bool column_matrix)
{
    auto mat = column_matrix ? Matrix(this->size, 1) : Matrix(1, this->size);
    for (uint i = 0; i < this->size; ++i)
    {
        double val;
        switch (state)
        {
        case Value:
            val = this->neurons[i].getValue();
            break;
        case Activated:
            val = this->neurons[i].getActivatedValue();
            break;
        case Derived:
            val = this->neurons[i].getDerivedValue();
            break;
        }
        if (column_matrix)
            mat.setValue(i, 0, val);
        else
            mat.setValue(0, i, val);
    }
    return mat;
}

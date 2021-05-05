#include "../include/Layer.hpp"

Layer::Layer(int size)
{
    this->n_neurons = size;
    for (uint i = 0; i < this->size(); ++i)
    {
        auto n = Neuron(0.00);
        this->neurons.push_back(n);
    }
}
Layer::Layer(std::vector<double> layer)
{
    this->n_neurons = layer.size();
    for (uint i = 0; i < this->size(); ++i)
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
void Layer::setValues(Eigen::RowVectorXd values)
{
    for (uint i = 0; i < this->size(); ++i)
    {
        this->neurons[i].setValue(values[i]);
    }
}

Eigen::MatrixXd Layer::as_matrix(NeuronValueState state, bool column_matrix)
{
    auto mat = column_matrix ? Eigen::MatrixXd(this->size(), 1) : Eigen::MatrixXd(1, this->size());
    for (uint i = 0; i < this->size(); ++i)
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
            mat(i, 0) = val;
        else
            mat(0, i) = val;
    }
    return mat;
}

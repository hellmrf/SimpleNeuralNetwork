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
        auto m = Eigen::MatrixXd::Random(this->topology[i], this->topology[i + 1]);
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
    this->layers[0] = layer;
}

/**
 * TODO: write that
 * 
 */
void NeuralNetwork::feedForward()
{
    // The first iteration needs de Values without actiavation.

    auto xi = this->layers[0].as_matrix(Value, false);
    auto Wi = this->weights[0];
    Eigen::MatrixXd next_layer = xi * Wi;
    this->layers[1].setValues(next_layer);

    for (uint i = 1; i < this->layers.size() - 1; ++i)
    {
        auto xi = this->layers[i].as_matrix(Activated, false);
        auto Wi = this->weights[i];
        Eigen::MatrixXd next_layer = xi * Wi;
        this->layers[i + 1].setValues(next_layer);
    }
}

std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann)
{
    bool begin = true;
    // for (auto layer : ann.layers)
    os << "[1]  " << ann.getLayer(0).as_matrix(Value, false) << std::endl;
    for (uint i = 1; i < ann.layers.size(); ++i)
    {
        os << "[" << i + 1 << "]  " << ann.getLayer(i).as_matrix(Activated, false) << std::endl;
    }

    return os;
}
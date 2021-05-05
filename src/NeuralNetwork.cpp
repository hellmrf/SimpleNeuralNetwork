#include "../include/NeuralNetwork.hpp"

NeuralNetwork::NeuralNetwork(std::vector<uint> topology)
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

void NeuralNetwork::setTarget(std::vector<double> target)
{
    if (target.size() != this->topology.back())
        throw(std::domain_error(StringStream::stringify("The target vector (", target.size(), ",) needs to be of the same size as the last layer of the network (", this->topology.back(), " neurons).")));
    else
        this->target = target;
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

Eigen::RowVectorXd NeuralNetwork::getOutputLayer(NeuronValueState state)
{
    return this->layers.back().as_matrix(state);
}

void NeuralNetwork::computeErrors()
{
    if (this->target.size() == 0)
        throw(std::logic_error(StringStream::stringify("You should define the target vector before computing the errors. Use ", Util::TColor::BLUE, "NeuralNetwork::setTarget(std::vector<double> target)", Util::TColor::RESET, " to do so.")));
    // Compute errors for each neuron
    auto outputLayer = this->getOutputLayer(Activated);
    this->outputErrors.clear();
    for (uint i = 0; i < outputLayer.size(); ++i)
    {
        double err = pow(outputLayer[i] - this->target[i], 2);
        this->outputErrors.push_back(err);
    }

    // Compute mean squared error
    this->mean_error = 0.0;
    for (auto err : this->outputErrors)
        this->mean_error += err;
    this->mean_error /= this->outputErrors.size();

    // Push to historical errors
    this->historicalErrors.push_back(this->mean_error);
}

std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann)
{
    os << Util::TColor::BLUE << " Input layer [1]  " << Util::TColor::RESET << ann.getLayer(0).as_matrix(Value, false) << std::endl;
    auto num_layers = ann.layers.size();
    for (uint i = 1; i < num_layers - 1; ++i)
        os << Util::TColor::BLUE << "Hidden layer [" << i + 1 << "]  " << Util::TColor::RESET << ann.getLayer(i).as_matrix(Activated, false) << std::endl;
    os << Util::TColor::BLUE << "Output layer [" << num_layers << "]  " << Util::TColor::RESET << ann.getLayer(num_layers - 1).as_matrix(Activated, false) << std::endl;

    return os;
}
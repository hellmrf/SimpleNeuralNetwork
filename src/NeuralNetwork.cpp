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
    if (layer.size() != this->topology.front())
        throw(std::domain_error(StringStream::stringify("The input vector (", layer.size(), ",) needs to be of the same size as the first layer of the network (", this->topology.front(), " neurons).")));
    else
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
    // The first iteration (input -> first layer) needs the Values without activation.

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
void NeuralNetwork::backPropagation()
{
    // Going from output layer to last hidden layer
    Eigen::RowVectorXd derived_output = this->getOutputLayer(Derived);
    Eigen::RowVectorXd gradient = derived_output.cwiseProduct(this->outputErrors);
    uint last_hidden_idx = this->layers.size() - 2;
    Eigen::RowVectorXd last_hidden_layer = this->layers[last_hidden_idx].as_matrix(Activated);
    Eigen::MatrixXd delta_output_to_hidden = (gradient.transpose() * last_hidden_layer).transpose();
    Eigen::MatrixXd new_weights = this->momentum * this->getWeights(last_hidden_idx) - this->learning_rate * delta_output_to_hidden;
    this->weights[last_hidden_idx] = new_weights;

    // Going from last hidden layer to input
    for (uint i = last_hidden_idx; i > 0; --i)
    {
        /* i is the current layer.
           We're computing the deltas between the current layer and the left one. */
        Layer layer = this->getLayer(i);
        Layer left_layer = this->getLayer(i - 1);
        Eigen::RowVectorXd layer_deriv = layer.as_matrix(Derived);
        Eigen::MatrixXd weight_matrix = this->getWeights(i);
        Eigen::MatrixXd left_weight_matrix = this->getWeights(i - 1);

        gradient *= weight_matrix.transpose();
        gradient = gradient.cwiseProduct(layer_deriv);

        // If the left layer is the input (0), we get the value Activated. Otherwise, we get it Derived.
        Eigen::RowVectorXd left_layer_neurons = (i - 1 == 0) ? left_layer.as_matrix(Value) : left_layer.as_matrix(Activated);

        Eigen::MatrixXd delta_weights = left_layer_neurons.transpose() * gradient;

        Eigen::MatrixXd new_weights = this->momentum * left_weight_matrix - this->learning_rate * delta_weights;
        this->weights[i - 1] = new_weights; // :)
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
    this->outputErrors = Eigen::RowVectorXd(outputLayer.size());
    this->outputMSE = Eigen::RowVectorXd(outputLayer.size());
    for (uint i = 0; i < outputLayer.size(); ++i)
    {
        // double err = pow(outputLayer[i] - this->target[i], 2);
        double err = outputLayer[i] - this->target[i];
        this->outputErrors[i] = err;
        this->outputMSE[i] = pow(err, 2);
    }

    // Compute mean squared error
    this->mean_error = 0.0;
    const uint N = this->outputErrors.size();
    for (uint i = 0; i < N; ++i)
        this->mean_error += this->outputMSE[i];
    this->mean_error = this->mean_error / N;

    // Push to historical errors
    this->historicalErrors.push_back(this->mean_error);
}

std::ostream &operator<<(std::ostream &os, const NeuralNetwork &ann)
{
    os << Util::TColor::BLUE << " Input layer [0]  " << Util::TColor::RESET << ann.getLayer(0).as_matrix(Value, false) << std::endl;
    auto num_layers = ann.layers.size();
    for (uint i = 1; i < num_layers - 1; ++i)
        os << Util::TColor::BLUE << "Hidden layer [" << i << "]  " << Util::TColor::RESET << ann.getLayer(i).as_matrix(Activated, false) << std::endl;
    os << Util::TColor::BLUE << "Output layer [" << num_layers - 1 << "]  " << Util::TColor::RESET << ann.getLayer(num_layers - 1).as_matrix(Activated, false) << std::endl;

    return os;
}
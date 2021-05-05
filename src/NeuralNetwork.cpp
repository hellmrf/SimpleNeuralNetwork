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
    // The first iteration needs the Values without actiavation.

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
    Eigen::RowVectorXd derived_output = this->getOutputLayer(Derived);
    Eigen::RowVectorXd gradient = derived_output.cwiseProduct(this->outputErrors);
    uint last_hidden_idx = this->layers.size() - 2;
    Eigen::RowVectorXd last_hidden_layer = this->layers[last_hidden_idx].as_matrix(Activated);
    Eigen::MatrixXd delta_output_to_hidden = (gradient.transpose() * last_hidden_layer).transpose();
    Eigen::MatrixXd new_weights = this->getWeights(last_hidden_idx) - delta_output_to_hidden;
    this->weights[last_hidden_idx] = new_weights;
    // Going from last hidden layer to input
    for (int i = last_hidden_idx; i > 0; --i)
    {
        Layer layer = this->getLayer(i);
        Layer left_layer = this->getLayer(i - 1);
        Eigen::RowVectorXd layer_deriv = layer.as_matrix(Derived);
        Eigen::RowVectorXd layer_activ = layer.as_matrix(Activated);
        Eigen::MatrixXd weight_matrix = this->getWeights(i);
        Eigen::MatrixXd left_weight_matrix = this->getWeights(i - 1);
        // Eigen::RowVectorXd derivedGrad = gradient * weight_matrix.transpose();
        auto derivedGrad = Eigen::RowVectorXd(layer.size());
        for (uint r = 0; r < weight_matrix.rows(); ++r)
        {
            double sum = 0;
            for (uint c = 0; c < weight_matrix.cols(); ++c)
            {
                sum += gradient[c] * weight_matrix(r, c);
            }
            derivedGrad[r] = sum * layer_activ[r];
        }
        Eigen::RowVectorXd left_layer_neurons = (i - 1 == 0) ? left_layer.as_matrix(Activated) : left_layer.as_matrix(Derived);
        Eigen::MatrixXd delta_weights = (derivedGrad.transpose() * left_layer_neurons).transpose();
        Eigen::MatrixXd new_weights = left_weight_matrix - delta_weights;
        this->weights[i - 1] = new_weights;
        gradient = derivedGrad;
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
    for (uint i = 0; i < outputLayer.size(); ++i)
    {
        // double err = pow(outputLayer[i] - this->target[i], 2);
        double err = outputLayer[i] - this->target[i];
        this->outputErrors[i] = err;
    }

    // Compute mean squared error
    this->mean_error = 0.0;
    const uint N = this->outputErrors.size();
    for (uint i = 0; i < N; ++i)
        this->mean_error += this->outputErrors[i];
    this->mean_error /= N;

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
#include <iostream>
#include <random>
#include <Eigen/Dense>
#include "Neuron.hpp"
#include "NeuralNetwork.hpp"
#include "Util.hpp"
#include "Statistics.hpp"

int main(int, char **)
{
    srand((unsigned)time(0));
    // Neuron n = Neuron(0.9);
    // std::cout << "Val: " << n.getValue() << std::endl;
    // std::cout << "Activated Val: " << n.getActivatedValue() << std::endl;
    // std::cout << "Derived Val: " << n.getDerivedValue() << std::endl;

    std::vector<uint> topology{3, 3, 3};
    std::vector<double> input{1., 2., 1.};

    NeuralNetwork ann = NeuralNetwork(topology);
    ann.setInputLayer(Layer(input));
    ann.setTarget(std::vector<double>{0., 0., 0.});

    std::cout << "==================================" << std::endl;
    std::cout << ann << std::endl;
    ann.feedForward();
    std::cout << "------- AFTER FEED-FORWARD -------" << std::endl;
    std::cout << ann << std::endl;

    std::cout << "==================================" << std::endl;

    ann.computeErrors();
    std::cout << "Mean error:" << std::endl;
    std::cout << ann.mean_error << std::endl;
    std::cout << "Output errors:" << std::endl;
    std::cout << ann.outputErrors << std::endl;
    std::cout << "Historical errors:" << std::endl;
    std::cout << ann.historicalErrors << std::endl;

    std::cout << "==================================" << std::endl;
    // std::cout << ann.getWeights(1) << std::endl;

    for (uint i = 0; i < ann.numLayers() - 1; ++i)
    {
        std::cout << StringStream::stringify(Util::TColor::CYAN, "        Layer ", i, " --> ", i + 1, Util::TColor::RESET) << std::endl;

        std::cout << ann.getWeights(i) << std::endl;
        std::cout << "----------" << std::endl;
    }
    ann.backPropagation();
    for (uint iter = 0; iter < 10; ++iter)
    {
        ann.feedForward();
        ann.computeErrors();
        ann.backPropagation();

        std::cout << "====== [" << iter << "] ======" << std::endl;
        for (uint i = 0; i < ann.numLayers() - 1; ++i)
        {
            std::cout << StringStream::stringify(Util::TColor::CYAN, "        Layer ", i + 1, " --> ", i + 2, Util::TColor::RESET) << std::endl;

            std::cout << ann.getWeights(i) << std::endl;
            std::cout << "----------" << std::endl;
        }
    }
    std::cout << "==================================" << std::endl;

    ann.computeErrors();
    std::cout << "Mean error:" << std::endl;
    std::cout << ann.mean_error << std::endl;
    std::cout << "Historical errors:" << std::endl;
    std::cout << ann.historicalErrors << std::endl;
    std::cout << "Output errors:" << std::endl;
    std::cout << ann.outputErrors << std::endl;

    std::cout << "==================================" << std::endl;
    std::cout << ann.getOutputLayer() << std::endl;

    // std::cout << ann.getWeights(1) << std::endl;

    return 0;
}

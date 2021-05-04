# Simple Neural Network

A Simple Neural Network implemented in C++.

## Dependencies

This project were built aiming minimal dependencies. However, Matrix arithmetic is a performance-critic thing, and the [Eigen](https://eigen.tuxfamily.org/) Library is _WAY_ faster than my naïve implementations.

You should install Eigen. In Ubuntu/Debian, you would do:

```shell
sudo apt install libeigen3-dev
```

and that's all.

You can also [download](https://gitlab.com/libeigen/eigen/-/releases/3.4-rc1) the headers and place it inside `/include/`, so that `/include/Eigen/Dense` is accessible.

## Compiling

This project use CMake to make things better. Just proceed with the usual compiling procedure:

```shell
$ mkdir build && cd build
$ cmake ..
$ make # compile everything
$ ./NeuralNetwork # execute :)
```

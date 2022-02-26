# Firmware Challenge

This library implements a Circular Buffer and a Encoder Reader.

## Requirements

You'll need the following requirements in your computer in order to build the
project:

- [CMake](https://cmake.org/install/) - tested version 3.22.2
- [GCC](https://gcc.gnu.org/install/) - tested version 5.4.0

## How to build the project

In order to build the project, open a terminal and follow these steps:

1. Go to the root folder of the project and create a build folder
    ```bash
    # Assuming you are in the build folder
    mkdir build && cd build
    ```
1. Run CMake to configure the project, and make to compile it
    ```bash
    cmake .. && make
    ```

## How to run the tests

We've used the [gtest](https://github.com/google/googletest) framework in order
to implement unit testing. In the [test CMakeLists](tests/CMakeLists.txt)
we are fetching the package so that it does not need to be installed in the
system.

To run the tests, in the same terminal you have compiled the project, you can
run the following command:
```bash
./tests/utest-CircularBuffer
./tests/utest-EncoderReader
```

The following ouput must be shown:
```bash
....
[----------] Global test environment tear-down
[==========] X tests from 1 test suite ran. (X ms total)
[  PASSED  ] X tests.
```
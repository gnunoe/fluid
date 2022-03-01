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

## Use docker

In Host computer:

1. Pull gcc image `docker pull gcc:9.4`
2. Go to the project directory `cd <ROOT_FOLDER_OF_PROJECT>
3. Start docker sharing the project `docker run -it --rm -v "$PWD":/home gcc:9.4.0`

This will open the docker with a terminal, inside docker:

1. Install cmake, we will use v3.22.2 
`wget https://github.com/Kitware/CMake/releases/download/v3.22.2/cmake-3.22.2-Linux-x86_64.sh -q -O /tmp/cmake-install.sh && chmod u+x /tmp/cmake-install.sh && mkdir /usr/bin/cmake && /tmp/cmake-install.sh --skip-license --prefix=/usr/bin/cmake && rm /tmp/cmake-install.sh`
2. `cd /home/build`
3. Remove previous generated files with `rm -rf *`
4. Run cmake and make. Use full path to invoque cmake
`/usr/bin/cmake/bin/cmake .. && make`
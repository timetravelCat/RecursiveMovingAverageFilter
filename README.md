# Recursive Moving Average Filter

An fast recursive moving average filter appropriate for large-sample scale.

## Features

* **Recursive implements**
* **Numerically stable**
* **written in c++, however use c lib only. (no stdlibc++)**
* **Fast in accepting new samples**
* **Requires lots of memory as much as non-recursive algorithms for numerical stable**
* **Supports buffer usage status for queue**

## limitations
* **Requires valid range of floating point, such as [-1,1] or [-10,10]**
* **Accuracy depends on range**
* **internally, float converted to int32_t, and stored in queue**
* **do not support dynamic buffer (memory decided by template parameter)**

## Getting Started

```C++
#include <rmaf/RecursiveMovingAverageFilter.hpp>
#include <rmaf/RecursiveMovingAverageFilterND.hpp>

using namespace RMAF;

int main(int argc, char const *argv[])
{
    // A simple 1D moving average filter
    // Specify range of data. assumed you have data with range [-10,10]
    // Specify Buffer size(200) & capacity(5) size (capacity can be changed by reset api)
    RecursiveMovingAverageFilter<getDigits(10.0f), 200> _rmaf{ 5, "rmaf 1" };

    // Insert data, return false if not pull
    _rmaf.push(0.0f);
    _rmaf.push(1.0f);
    _rmaf.push(2.0f);
    _rmaf.push(3.0f);
    _rmaf.push(4.0f);

    // return true if full
    // Internally, Algorithm implemented as recursive,
    // buffer = buffer + new - old
    // In order to preserve long time numerical stability, requires queue size as much as capacity.
    float result;
    if(rmaf.push(5.0f, &result)) {
        // check result data, (1+2+3+4+5)/5 saved in result.
    }

    // Capacity could be changed by reset method.
    // requires at least 3 samples before return true.
    _rmaf.reset(3);

    // You Can Check (most)memory required by queue.
    // All instances (limits to 100, change MAX_INSTANCE_NUM in Buffer.cpp ) with name will be printed to your console.
    PrintBufferStatus();
    
    // N dimension overlapped moving average filter.
    // 3-Dimension limits with 10.0f, with buffer 10,5,3 / capacity 2,3,2 initialization
    RecursiveMovingAverageFilterND<getDigits(10.0f), 10, 5, 3> _RecursiveMovingAverageFilterND{ "test_RMAFND", 2, 3, 2 };

    // Data Looks like
    // first queue 1.0 / 2.0 / 3.0 / 4.0 / 5.0 / 6.0 / 7.0 / 8.0
    // second queue         2.5 / 3.5 / 4.5 / 5.5 / 6.5 / 7.5       //average of 2 sample
    // third queue                      4.5 / 5.5 / 6.5             //average of 3 sample
    // result                                   6.0                 //average of 2 sample
    _RecursiveMovingAverageFilterND.push(1.0f);
    _RecursiveMovingAverageFilterND.push(2.0f);
    _RecursiveMovingAverageFilterND.push(3.0f);
    _RecursiveMovingAverageFilterND.push(4.0f);
    _RecursiveMovingAverageFilterND.push(5.0f);
    _RecursiveMovingAverageFilterND.push(6.0f);
    _RecursiveMovingAverageFilterND.push(7.0f);

    if(_RecursiveMovingAverageFilterND.push(8.0f, &result))
    {
        // Check result data, should be 6.0
    }


  return 0;
}
```

### Prerequisites

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++14** standard, i.e. *MSVC*,
*GCC*, *Clang*

### Installing

It is fairly easy to install the project, all you need to do is clone if from
[GitHub](https://github.com/timetravelerCat/RecursiveMovingAverageFilter) or
[generate a new repository from it](https://github.com/timetravelerCat/RecursiveMovingAverageFilter/generate)
(also on **GitHub**).

If you wish to clone the repository, rather than generate from it, you simply need
to run:

```bash
git clone https://github.com/timetravelerCat/RecursiveMovingAverageFilter/
```

To install an already built project, you need to run the `install` target with CMake.
For example:

```bash
cmake --build build --target install --config Release

# a more general syntax for that command is:
cmake --build <build_directory> --target install --config <desired_config>
```

## Building the project

To build the project, all you need to do, ***after correctly
[installing the project](README.md#Installing)***, is run a similar **CMake** routine
to the the one below:

```bash
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target install
```

> ***Note:*** *The custom ``CMAKE_INSTALL_PREFIX`` can be omitted if you wish to
install in [the default install location](https://cmake.org/cmake/help/latest/module/GNUInstallDirs.html).*

More options that you can set for the project can be found in the
[`cmake/StandardSettings.cmake` file](cmake/StandardSettings.cmake). For certain
options additional configuration may be needed in their respective `*.cmake` files
(i.e. Conan needs the `CONAN_REQUIRES` and might need the `CONAN_OPTIONS` to be setup
for it work correctly; the two are set in the [`cmake/Conan.cmake` file](cmake/Conan.cmake)).

## Running the tests

By default, the template uses [catch2](https://github.com/catchorg/Catch2/)
for unit testing. Unit testing can be disabled in the options, by setting the
`ENABLE_UNIT_TESTING` (from
[cmake/StandardSettings.cmake](cmake/StandardSettings.cmake)) to be false. To run
the tests, simply use CTest, from the build directory, passing the desire
configuration for which to run tests for. An example of this procedure is:

```make
make test
```
or
```bash
cd build          # if not in the build directory already
ctest -C Release  # or `ctest -C Debug` or any other configuration you wish to test

# you can also run tests with the `-VV` flag for a more verbose output (i.e.
#GoogleTest output as well)
```

## Versioning

This project makes use of [SemVer](http://semver.org/) for versioning. A list of
existing versions can be found in the
[project's releases](https://github.com/timetravelerCat/RecursiveMovingAverageFilter/releases).


## Development Requirements

* **CMake v3.15+** - found at [https://cmake.org/](https://cmake.org/)

* **Static analyzers** *Cppcheck*

* **Unit testing** *Catch2*

* **Ccache** 

## Authors

* **timetravelCat** - [@Timetraveler](https://github.com/timetravelCat)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

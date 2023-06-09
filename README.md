# meatball

This is a hobbyist's attempt at machine learning by creating a chess engine.

The brains of the chess engine can be broken up into three distinct categories:

1. Board representation - bitboard
2. Search - Monte Carlo Tree Search (MCTS)
3. Evaluation - deep neural network

NOTE: This code is written with readability in mind and is not meant to be optimized (although certain optimizations may occur in future releases). There are also instances in this code that can be replaced with data structures or functions in the C++ standard library, but that's no fun so I decided to implement them as an exercise.

# Installation

This project was built using C++17, so make sure you have at least C++17 installed on your system.

Clone the directory and build the executable

```
git clone https://github.com/hgducharme/meatball.git
cd meatball/
make meatball
```

If successful, you should see the executable `/bin/meatball`

# Tests

To run the tests make sure you have [googletest 1.13.0](https://github.com/google/googletest/releases/tag/v1.13.0) and `cmake` installed on your system.

To install `googletest`, download the zip file, unzip it, then

```
cd /path/to/googletest/
mkdir install
cd install/
cmake ..
make
make install
```

Next, edit the `GOOGLETEST` variable inside `meatball/Makefile` to point to where `googletest` was installed. Replace `/usr/local/lib` with the directory that houses your `libgtest.a` and `libgtest_main.a` files.

```
GOOGLETEST := -L/usr/local/lib -lgtest -lgtest_main
```

Build and run the tests:

```
make tests
./bin/tests
```

## Test coverage

Make sure you have `gcov` and `gcovr` installed on your system.

```
make coverage
```

The `test_coverage/` directory will contain `.gcov` files generated by `gcov` and html files generated by `gcovr`.

To see the HTML coverage report just open the file `meatball/test_coverage/coverage.html` in your browser.
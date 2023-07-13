# meatball

This is a hobbyist's attempt at machine learning by creating a chess engine.

# Features

- Board Representation
  - [Bitboards](https://www.chessprogramming.org/Bitboards)
- Move Generation
  - [Magic bitboards](https://www.chessprogramming.org/Magic_Bitboards)
- Search
  - [Monte Carlo Tree Search (MCTS)](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)
- Evaluation
  - [Deep neural network](https://en.wikipedia.org/wiki/Deep_learning)

# Installation

NOTE: This project was built using C++17.

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
make test-coverage
```

The `test_coverage/` directory will contain `.gcov` files generated by `gcov` and html files generated by `gcovr`.

To see the HTML coverage report just open `/your/full/path/to/meatball/test_coverage/coverage.html` in the browser.

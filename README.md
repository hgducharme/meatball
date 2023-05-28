# meatball

This is a hobbyist's attempt at machine learning by creating a chess engine

The brains of the chess engine can be broken up into three distinct categories:

1. Board representation - bitboard
2. Search - Monte Carlo Tree Search (MCTS)
3. Evaluation - deep neural network

# Installation

Clone the directory

```
git clone https://github.com/hgducharme/meatball.git
cd meatball/
```

Build the project

```
make
```

If successful, you should see the executable as `meatball.app` in the root directory.

# Tests

To run the tests make sure you have [googletest 1.13.0](https://github.com/google/googletest/releases/tag/v1.13.0) installed on your system and `cmake` installed, then edit the Makefile to point to your installation of `googletest`.

To install `googletest`, download the zip file and unzip it, then

```
cd /path/to/googletest/
mkdir install
cd install/
cmake ..
make
make install
```

Next, edit the `GOOGLETEST` variable inside the makefile to point to where `googletest` was installed. Replace `/usr/local/lib` with the directory that houses your `libgtest.a` and `libgtest_main.a` files.

```
GOOGLETEST := -L/usr/local/lib -lgtest -lgtest_main
```

Build the tests using

```
make tests
```
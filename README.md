# meatball

This is a hobbyist's attempt at machine learning by creating a chess engine in C++.

## Features

Consider reading [the wiki](https://github.com/hgducharme/meatball/wiki/) for more information on the theory behind some of the engine's components.

- Board Representation
  - [Bitboards](https://www.chessprogramming.org/Bitboards)
- Move Generation
  - [Magic bitboards](https://www.chessprogramming.org/Magic_Bitboards)
- Search
  - [Monte Carlo Tree Search (MCTS)](https://en.wikipedia.org/wiki/Monte_Carlo_tree_search)
- Evaluation
  - [Deep neural network](https://en.wikipedia.org/wiki/Deep_learning)

This code is written with readability in mind and is not meant to be fully optimized.

## Installation

### Dependencies

- C++17

This project was built using C++17, so make sure you have at least C++17 installed on your system.

Clone the directory and build the executable

```bash
git clone https://github.com/hgducharme/meatball.git
cd meatball/
make meatball
```

If successful, you should see the executable `/bin/meatball`

## Tests

### Dependencies

- [googletest 1.13.0](https://github.com/google/googletest/releases/tag/v1.13.0)
- cmake for building googletest

### Running tests using Docker

1. Make sure the docker daemone is already running (see: [starting docker daemon](https://docs.docker.com/config/daemon/start/))
2. Run the test suite

```bash
cd /path/to/meatball/
make docker-tests
```

### Running tests locally

To install `googletest-1.13.0`:

```bash
cd /tmp
wget https://github.com/google/googletest/archive/refs/tags/v1.13.0.tar.gz
tar xf v1.13.0.tar.gz
cd googletest-1.13.0
mkdir install
cd install
cmake ..
make
make install
cd ../../
rm -rf googletest-1.13.0 && v1.13.0.tar.gz
```

Next, edit the `GOOGLETEST` variable inside `meatball/Makefile` to point to where `googletest` was installed. Replace `/usr/local/lib` with the directory that houses your `libgtest.a` and `libgtest_main.a` files.

```make
GOOGLETEST := -L/usr/local/lib -lgtest -lgtest_main
```

Build and run the tests:

```bash
make tests
./bin/tests
```

To build and run only the unit tests:

```bash
make unit_tests
./bin/unit_tests
```

To build (and run) only the inegration tests:

```bash
make integration_tests
./bin/integration_tests
```

### Test coverage

This only works locally. Make sure you have `gcov` and `gcovr` installed on your system:

- `gcov` is included with `gcc` and `clang`
- `gcovr` can be installed with `pip` and `brew`

```bash
make coverage
```

The `test_coverage/` directory will contain `.gcov` files generated by `gcov` and html files generated by `gcovr`.

To see the HTML coverage report just open the file `meatball/test_coverage/html/coverage.html` in your browser.

## Debugging move generation using the perft

It can be difficult to know where to start debugging the move generation when a test case fails because the number of calculated nodes don't match up with the expected number of nodes. To achieve a more specific error output we can do a [perft divide](https://www.chessprogramming.org/Perft#Divide). For each top level move, the perft divide function will show the number of child nodes. So in order to debug move generation in a practical way, the following steps are recommended:

1. Go to your stockfish repo and make sure the executable has been built.
2. Start the executable `./stockfish`.
3. Run the commands in the shell: `position startpos` and then `go perft [depth]`. You should see the number of nodes that fall under each top level move. You can recurse down the tree to get more and more precise results.
4. In `test_movegenerator.cpp`, make sure the `showDivideOutput` argument in the `perft()` calls are set to `true`. This will print the divide output to the console.
5. Compare the results.

## Docker Support

If you have docker installed then you can do any of the following things within a docker container:

1. Build the source code
2. Run a linter
3. Run the test suite

Steps to use docker:

1. Ensure the docker daemon is running and go the the project root

  ```bash
  cd /path/to/meatball
  ```

2. Build the source code:

  ```bash
  make docker-build BUILD_FLAGS="CXX=g++ DEBUG_LEVEL=0 OPTIMIZATION_LEVEL=3"
  ```

3. Run the linter

  ```bash
  cd /path/to/meatball/
  make docker-linter
  ```

4. Run the test suite

  ```bash
  cd /path/to/meatball/
  make docker-tests
  ```

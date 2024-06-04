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

Make sure to have docker installed on your system, that is the only dependency.

Clone the directory and build the executable

```bash
git clone https://github.com/hgducharme/meatball.git
cd meatball/
make docker-meatball
```

If successful, the terminal should be attached to the container running the executable.

## Tests

Build and run the tests:

```bash
make docker_tests
```

To build (and run) only the unit tests:

```bash
make docker_unit_tests
```

To build (and run) only the inegration tests:

```bash
make docker_integration_tests
```

### Test coverage

```bash
make docker_coverage
```

To see the HTML coverage report just open the file `meatball/test_coverage/html/coverage.html` in your browser.

## Debugging move generation using the perft

It can be difficult to know where to start debugging the move generation when a test case fails because the number of calculated nodes don't match up with the expected number of nodes. To achieve a more specific error output we can do a [perft divide](https://www.chessprogramming.org/Perft#Divide). For each top level move, the perft divide function will show the number of child nodes. So in order to debug move generation in a practical way, the following steps are recommended:

1. Go to your stockfish repo and make sure the executable has been built.
2. Start the executable `./stockfish`.
3. Run the commands in the shell: `position startpos` and then `go perft [depth]`. You should see the number of nodes that fall under each top level move. You can recurse down the tree to get more and more precise results.
4. In `test_movegenerator.cpp`, make sure the `showDivideOutput` argument in the `perft()` calls are set to `true`. This will print the divide output to the console.
5. Compare the results.

TODO:

```bash
make stockfish
```

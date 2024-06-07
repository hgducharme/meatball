SHELL = /bin/sh
appname := meatball

# -------------------------------------- #
# Paths and executables
# -------------------------------------- #
PROJECT_DIR := .
SOURCE_DIR := $(PROJECT_DIR)/src
TEST_DIR := $(PROJECT_DIR)/test
UNIT_TEST_DIR := $(TEST_DIR)/unit
INTEGRATION_TEST_DIR := $(TEST_DIR)/integration
BUILD_DIR := $(PROJECT_DIR)/build
BIN_DIR := $(PROJECT_DIR)/bin
COVERAGE_DIR := $(PROJECT_DIR)/test_coverage
TEST_UTILS_DIR := $(TEST_DIR)/utils

EXECUTABLE = $(BIN_DIR)/$(appname)
TEST_EXECUTABLE = $(BIN_DIR)/tests
UNIT_TEST_EXECUTABLE = $(BIN_DIR)/unit_tests
INTEGRATION_TEST_EXECUTABLE = $(BIN_DIR)/integration_tests

# -------------------------------------- #
# Compiling configuration
# -------------------------------------- #
# Compiler
CXX := clang++

# Compiler flags
CPP := 17
DEBUG_LEVEL := 0
OPTIMIZATION_LEVEL := 1
COVERAGE := --coverage

CXXFLAGS := -Wall -Wextra -fdiagnostics-color=always -fPIC -std=c++$(CPP) -O$(OPTIMIZATION_LEVEL) -g$(DEBUG_LEVEL) $(COVERAGE)

# C PreProcessor flags, generally used for path management, dependency file generation, and dumping preprocessor state
# Include source subdirectories and generate dependency files during compilation
source_subdirectories := $(shell find $(SOURCE_DIR) -type d)
include_source_subdirectories := $(addprefix --include-directory=, $(source_subdirectories))
CPPFLAGS := $(include_source_subdirectories) --write-user-dependencies -MP

# Compilation command
COMPILE.cpp := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) --compile

# -------------------------------------- #
# Linking configuration
# -------------------------------------- #
# Tell the linker to look inside these directories to find the libraries passed into LDLIBS
# flags should look like: "-L/path/to/lib/dir"
# LDFLAGS :=

# Link to libraries
# LDLIBS := 

LINK.cpp := $(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)

# -------------------------------------- #
# Libraries
# -------------------------------------- #
# googletest flags for the linker
GOOGLETEST := --library-directory /usr/local/lib -lgtest -lgtest_main

# -------------------------------------- #
# Files
# -------------------------------------- #
# Source code files
sourcefiles := $(shell find $(SOURCE_DIR) -name "*.cpp")
objectfiles := $(sourcefiles:%.cpp=$(BUILD_DIR)/%.o)
sourcefiles_without_main = $(filter-out $(SOURCE_DIR)/main.cpp, $(sourcefiles))
objectfiles_without_main = $(filter-out $(BUILD_DIR)/./src/main.o, $(objectfiles))

# Test code files
test_utility_sourcefiles := $(shell find $(TEST_UTILS_DIR) -name "*.cpp")
test_utility_objectfiles := $(test_utility_sourcefiles:%.cpp=$(BUILD_DIR)/%.o)

unit_test_sourcefiles := $(shell find $(UNIT_TEST_DIR) -name "test_*.cpp")
unit_test_objectfiles := $(unit_test_sourcefiles:%.cpp=$(BUILD_DIR)/%.o)

integration_test_sourcefiles := $(shell find $(INTEGRATION_TEST_DIR) -name "test_*.cpp")
integration_test_objectfiles := $(integration_test_sourcefiles:%.cpp=$(BUILD_DIR)/%.o)

test_sourcefiles := $(unit_test_sourcefiles) $(integration_test_sourcefiles) $(test_utility_sourcefiles)
test_objectfiles := $(unit_test_objectfiles) $(integration_test_objectfiles) $(test_utility_objectfiles)

# All files
all_sourcefiles := $(sourcefiles) $(test_sourcefiles)
all_objectfiles := $(objectfiles) $(test_objectfiles)

# Files generated by gcov for test coverage
gcov_files = $(shell find $(BUILD_DIR) -name "*.gcno")

# -------------------------------------- #
# Targets
# -------------------------------------- #
.PHONY: all clean $(BIN_DIR) $(BUILD_DIR) $(COVERAGE_DIR) .DEFAULT_GOAL

all: $(appname) tests

.DEFAULT_GOAL := $(appname)

$(appname): $(EXECUTABLE)

# Build the source code executable
$(EXECUTABLE): $(objectfiles) | $(BIN_DIR)
	@echo
	@echo "Building: $@"
	@echo "Linking file(s): $^"
	$(LINK.cpp) $^ $(LDLIBS) --output $@

# Build the test executable by linking source objects (without main.o) and test objects
tests: $(objectfiles_without_main) $(test_objectfiles) | $(BIN_DIR)
	@echo
	@echo "Building: $@"
	@echo "Linking file(s): $^"
	$(LINK.cpp) $^ $(GOOGLETEST) --output $(TEST_EXECUTABLE)

# Build the unit tests executable by linking source objects (without main.o) and unit test objects
unit_tests: $(objectfiles_without_main) $(unit_test_objectfiles) $(test_utility_objectfiles) | $(BIN_DIR)
	@echo
	@echo "Building: $@"
	@echo "Linking file(s): $^"
	$(LINK.cpp) $^ $(GOOGLETEST) --output $(UNIT_TEST_EXECUTABLE)

# Build the integration tests executable by linking source objects (without main.o) and integration test objects
integration_tests: $(objectfiles_without_main) $(integration_test_objectfiles) $(test_utility_objectfiles) | $(BIN_DIR)
	@echo
	@echo "Building: $@"
	@echo "Linking file(s): $^"
	$(LINK.cpp) $^ $(GOOGLETEST) --output $(INTEGRATION_TEST_EXECUTABLE)

# Compile .cpp into .o
$(objectfiles) $(test_objectfiles): $(BUILD_DIR)/%.o: %.cpp
	@echo
	@echo "Compiling: '$<'"
	mkdir -p $(dir $@)
	$(COMPILE.cpp) $< --output $@

coverage: tests | $(COVERAGE_DIR)
	@echo
	@echo "Generating test coverage data..."
	gcov --color $(sourcefiles_without_main) -o=$(BUILD_DIR)/src
	mv *.gcov $(COVERAGE_DIR)/gcov
	gcovr --exclude-unreachable-branches --exclude-throw-branches --decisions --html-details $(COVERAGE_DIR)/html/coverage.html $(BUILD_DIR)/src

# -------------------------------------- #
# Folder targets
# -------------------------------------- #
$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(COVERAGE_DIR):
	mkdir -p $@/gcov
	mkdir -p $@/html

# -------------------------------------- #
# Clean
# -------------------------------------- #
clean:
	$(RM) -r $(BIN_DIR) $(BUILD_DIR) $(COVERAGE_DIR)

clean-tests:
	$(RM) -r $(TEST_EXECUTABLE) $(BUILD_DIR)/test

clean-coverage:
	$(RM) -r $(COVERAGE_DIR)

# -------------------------------------- #
# Dependencies
# -------------------------------------- #
dependencies := $(all_objectfiles:.o=.d)

-include $(dependencies)
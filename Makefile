SHELL = /bin/sh
appname := meatball

# -------------------------------------- #
# Paths and executables
# -------------------------------------- #
PROJECT_DIR := .
SOURCE_DIR := $(PROJECT_DIR)/src
TEST_DIR := $(PROJECT_DIR)/test
BUILD_DIR := $(PROJECT_DIR)/build
BIN_DIR := $(PROJECT_DIR)/bin
COVERAGE_DIR := $(PROJECT_DIR)/test_coverage

EXECUTABLE = $(BIN_DIR)/$(appname)
TEST_EXECUTABLE = $(BIN_DIR)/tests

# -------------------------------------- #
# Compiling configuration
# -------------------------------------- #
# Compiler
CXX := clang++

# Compiler flags
DEBUG = -g
COVERAGE := -O1 -fPIC --coverage # (--coverage is a synonym for: -fprofile-arcs -ftest-coverage)
CXXFLAGS := -Wall -Wextra -fdiagnostics-color=always -std=c++17 $(DEBUG) $(COVERAGE)

# C PreProcessor flags, generally used for path management, dependency file generation, and dumping preprocessor state
# Include source subdirectories and generate dependency files during compilation
source_subdirectories := $(shell find $(SOURCE_DIR) -type d)
include_source_subdirectories := $(addprefix --include-directory=, $(source_subdirectories))
CPPFLAGS := $(include_source_subdirectories) --write-user-dependencies -MP

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
test_sourcefiles := $(shell find $(TEST_DIR) -name "test_*.cpp")
test_objectfiles := $(test_sourcefiles:%.cpp=$(BUILD_DIR)/%.o)

# All files
all_sourcefiles := $(sourcefiles) $(test_sourcefiles)
all_objectfiles := $(objectfiles) $(all_objectfiles)

# Files generated by gcov for test coverage
gcov_files = $(shell find $(BUILD_DIR) -name "*.gcno")

# -------------------------------------- #
# Targets
# -------------------------------------- #
.PHONY: all clean $(BIN_DIR) $(BUILD_DIR) $(COVERAGE_DIR)

all: $(appname) tests

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
	./$(TEST_EXECUTABLE)

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
	mv *.gcov $(COVERAGE_DIR)/
	gcovr --html-details $(COVERAGE_DIR)/coverage.html $(BUILD_DIR)/src

# -------------------------------------- #
# Folder targets
# -------------------------------------- #
$(BIN_DIR):
	mkdir -p $@

$(BUILD_DIR):
	mkdir -p $@

$(COVERAGE_DIR):
	mkdir -p $@

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
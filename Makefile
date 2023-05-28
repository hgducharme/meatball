appname := meatball

# -------------------------------------- #
# Compiling and Linking Configuration
# -------------------------------------- #
# Compiler
CXX := clang++

# Compiler flags
# CXXFLAGS = 

# C PreProcessor flags
CPPFLAGS := -g -fdiagnostics-color=always -std=c++17

# Tell the linker to look inside these directories to find the libraries passed into LDLIBS
# flags should look like: "-L/path/to/lib/dir"
# LDFLAGS := 

# Link to libraries
# LDLIBS := 

# Link the google test library
GOOGLETEST := -L/usr/local/lib -lgtest -lgtest_main

# -------------------------------------- #
# Folders
# -------------------------------------- #
PROJECT_DIR=.
SOURCE_DIR=$(PROJECT_DIR)/src
TEST_DIR=$(PROJECT_DIR)/test
BUILD_DIR=$(PROJECT_DIR)/build
BIN_DIR=$(PROJECT_DIR)/bin

# -------------------------------------- #
# Executables
# -------------------------------------- #
EXECUTABLE=$(BIN_DIR)/$(appname)
TEST_EXECUTABLE=$(BIN_DIR)/tests

# -------------------------------------- #
# Paths
# -------------------------------------- #
sourcefiles := $(shell find $(SOURCE_DIR) -name "*.cpp")
objectfiles := $(sourcefiles:%=$(BUILD_DIR)/%.o)

test_sourcefiles := $(shell find $(TEST_DIR) -name "test_*.cpp")
test_objectfiles := $(test_sourcefiles:%=$(BUILD_DIR)/%.o)

# -------------------------------------- #
# Misc
# -------------------------------------- #
.PHONY: all clean distclean $(BIN_DIR) $(BUILD_DIR)

all: $(appname)

depend: .depend

.depend: $(sourcefiles)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

# -------------------------------------- #
# Targets
# -------------------------------------- #
$(appname): $(EXECUTABLE)

# Build the source code executable
$(EXECUTABLE): $(objectfiles) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(objectfiles) -o $(EXECUTABLE) $(LDLIBS)

# Compile and link the object files to the .cpp files
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# Build the test code executable
tests: $(test_objectfiles) | $(BIN_DIR)
	$(CXX) $(CPPFLAGS) $(test_objectfiles) -o $(TEST_EXECUTABLE) $(GOOGLETEST)

# -------------------------------------- #
# Folders
# -------------------------------------- #

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# -------------------------------------- #
# Clean
# -------------------------------------- #
clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(BIN_DIR)

distclean:
	$(RM) *~ .depend

include .depend
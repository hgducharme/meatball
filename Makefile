appname := meatball

# -------------------------------------- #
# Paths and executables
# -------------------------------------- #
PROJECT_DIR := .
SOURCE_DIR := $(PROJECT_DIR)/src
TEST_DIR := $(PROJECT_DIR)/test
BUILD_DIR := $(PROJECT_DIR)/build
BIN_DIR := $(PROJECT_DIR)/bin
source_subdirectories := $(shell find $(SOURCE_DIR) -type d)

EXECUTABLE = $(BIN_DIR)/$(appname)
TEST_EXECUTABLE = $(BIN_DIR)/tests

# -------------------------------------- #
# Compiling configuration
# -------------------------------------- #
# Compiler
CXX := clang++

# Compiler flags
CXXFLAGS := -Wall -Wextra -g -fdiagnostics-color=always -std=c++17

# C PreProcessor flags, generally used for path management, dependency file generation, and dumping preprocessor state
# Include source subdirectories and generate dependency files during compilation
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
# Link the google test library
GOOGLETEST := --library-directory /usr/local/lib -lgtest -lgtest_main

# -------------------------------------- #
# Files
# -------------------------------------- #
sourcefiles := $(shell find $(SOURCE_DIR) -name "*.cpp")
objectfiles := $(sourcefiles:%=$(BUILD_DIR)/%.o)

test_sourcefiles := $(shell find $(TEST_DIR) -name "test_*.cpp")
test_objectfiles := $(test_sourcefiles:%=$(BUILD_DIR)/%.o)

all_sourcefiles := $(sourcefiles) $(test_sourcefiles)
all_objectfiles := $(objectfiles) $(all_objectfiles)

# -------------------------------------- #
# Targets
# -------------------------------------- #
.PHONY: all clean $(BIN_DIR) $(BUILD_DIR)

all: $(appname)

$(appname): $(EXECUTABLE)

# Link the object files together and build the source code executable
$(EXECUTABLE): $(objectfiles) | $(BIN_DIR)
	$(LINK.cpp) $^ --output $@ $(LDLIBS)

# Link the object files together and build the test executable
tests: $(test_objectfiles) | $(BIN_DIR)
	$(LINK.cpp) $^ --output $(TEST_EXECUTABLE) $(GOOGLETEST)

# Compile the source code files into .o files
$(BUILD_DIR)/%.cpp.o: %.cpp
	mkdir -p $(dir $@)
	$(COMPILE.cpp) $< --output $@

# -------------------------------------- #
# Folder targets
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

# -------------------------------------- #
# Dependencies
# -------------------------------------- #
dependencies := $(all_objectfiles:.o=.d)

-include $(dependencies)
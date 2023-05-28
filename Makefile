appname := meatball

# -------------------------------------- #
# Compiling and Linking Configuration
# -------------------------------------- #
# Compiler
CXX := clang++

# C PreProcessor flags
CPPFLAGS := -g -fdiagnostics-color=always -std=c++17

# Tell the linker to look inside these directories to find the libraries passed into LDLIBS
# flags should look like: "-L/path/to/lib/dir"
# LDFLAGS := 

# Link to libraries
# LDLIBS := 

# Link the google test library found in /usr/local/lib
GOOGLETEST := -L/usr/local/lib -lgtest -lgtest_main

# -------------------------------------- #
# Folders
# -------------------------------------- #
PROJECT_DIR=.
SOURCE_DIR=$(PROJECT_DIR)/src
TEST_DIR=$(PROJECT_DIR)/test
BUILD_DIR=$(PROJECT_DIR)/build

# -------------------------------------- #
# Executables
# -------------------------------------- #
EXECUTABLE=$(appname).app
TEST_EXECUTABLE=$(TEST_DIR)/tests.out

# -------------------------------------- #
# Paths
# -------------------------------------- #
sourcefiles := $(shell find $(SOURCE_DIR) -name "*.cpp")
objectfiles := $(patsubst %.cpp, %.o, $(sourcefiles))

test_sourcefiles := $(shell find $(TEST_DIR) -name "test_*.cpp")
test_objectfiles := $(patsubst %.cpp, %.o, $(test_sourcefiles))

all_sourcefiles := $(sourcefiles) $(test_sourcefiles)
all_objectfiles := $(objectfiles) $(test_objectfiles)

# -------------------------------------- #
# Misc
# -------------------------------------- #
.PHONY: all clean distclean

all: $(appname)

depend: .depend

.depend: $(sourcefiles)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

# -------------------------------------- #
# Targets
# -------------------------------------- #
$(appname): $(objectfiles)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(objectfiles) -o $(EXECUTABLE) $(LDLIBS)

tests: $(test_objectfiles)
	$(CXX) $(CPPFLAGS) $(test_objectfiles) -o $(TEST_EXECUTABLE) $(GOOGLETEST)

# -------------------------------------- #
# Clean
# -------------------------------------- #

clean:
	$(RM) $(all_objectfiles) $(EXECUTABLE) $(TEST_EXECUTABLE)

distclean:
	$(RM) *~ .depend

include .depend
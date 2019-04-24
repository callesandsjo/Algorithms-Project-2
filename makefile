ifeq ($(OS), Windows_NT)
	INCLUDES := Includes\\
	BUILD := Build\\
	BIN := Bin\\
	EXECUTABLE := $(BIN)AVLTree.exe
	SOURCE := Source\\
	DELETE := del
else
	INCLUDES := Includes/
	BUILD := Build/
	BIN := Bin/
	EXECUTABLE := $(BIN)AVLTree
	SOURCE := Source/
	DELETE := rm
endif

CPP := g++
CPPFLAGS := -std=c++17 -Wall -Wextra -Wpedantic -pedantic-errors -O0 -Werror

all: $(EXECUTABLE)

$(EXECUTABLE): $(BUILD)Tests.o
	$(CPP) $(CPPFLAGS) $(BUILD)Tests.o -o $(EXECUTABLE)

$(BUILD)Tests.o: $(SOURCE)Tests.cpp $(INCLUDES)TestingBase.hpp $(INCLUDES)TestAVLTree.hpp
	$(CPP) $(CPPFLAGS) -c $(SOURCE)Tests.cpp -I$(INCLUDES) -o $(BUILD)Tests.o

clean:
	-$(DELETE) $(EXECUTABLE) $(BUILD)Tests.o
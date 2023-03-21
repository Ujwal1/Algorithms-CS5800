# CXX = g++
# CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
# LDFLAGS =
# SRC_DIR = .
# BUILD_DIR = build
# TARGET = hash

# SRCS = $(wildcard $(SRC_DIR)/*.cpp)
# OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# .PHONY: all clean

# all: $(BUILD_DIR)/$(TARGET)

# $(BUILD_DIR)/$(TARGET): $(OBJS)
# 	$(CXX) $(LDFLAGS) $^ -o $@

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
# 	$(CXX) $(CXXFLAGS) -c $< -o $@

# $(BUILD_DIR):
# 	mkdir -p $@

# clean:
# 	rm -rf $(BUILD_DIR)

CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17
LDFLAGS =
SRC_DIR = .
BUILD_DIR = build
TARGET = hash

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
SRCS := $(filter-out $(SRC_DIR)/$(TARGET).cpp, $(SRCS))
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all clean

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(SRC_DIR)/$(TARGET).cpp $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(SRC_DIR)/hashTable.h | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@

clean:
	rm -rf $(BUILD_DIR)

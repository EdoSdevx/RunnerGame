# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -I./src -I./src/include
LDFLAGS = -L./src/lib -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -mconsole


# Directories
SRC_DIR = src
BUILD_DIR = build
TARGET = runner.exe

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

# Build rule for object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Final linking step
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Clean build artifacts
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(TARGET) del $(TARGET)

# Optional: Run the game
run: $(TARGET)
	$(TARGET)

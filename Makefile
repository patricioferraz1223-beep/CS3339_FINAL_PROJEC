# ===============================
# Compiler
# ===============================
CXX = g++

# ===============================
# Compiler Flags
# ===============================
CXXFLAGS = -Wall -std=c++17

# ===============================
# Output Executable Name
# ===============================
TARGET = simulator

# ===============================
# Source Files (edit if needed)
# ===============================
SRCS = main.cpp pc.cpp alu.cpp control.cpp register_file.cpp instruction_memory.cpp data_memory.cpp

# ===============================
# Object Files (auto-generated)
# ===============================
OBJS = $(SRCS:.cpp=.o)

# ===============================
# Default Target
# ===============================
all: $(TARGET)

# ===============================
# Link Object Files → Executable
# ===============================
$(TARGET): $(OBJS)
	g++ $(CXXFLAGS) -o $(TARGET) $(OBJS)

# ===============================
# Compile .cpp → .o
# ===============================
%.o: %.cpp
	g++ $(CXXFLAGS) -c $< -o $@

# ===============================
# Run the program
# ===============================
run: all
	./$(TARGET)

# ===============================
# Clean build files (Windows)
# ===============================
clean:
	del /Q $(OBJS) $(TARGET) 2>nul

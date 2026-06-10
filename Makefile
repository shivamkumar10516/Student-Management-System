 # Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g
TARGET = student_management_system

# Source files
SOURCES = main.cpp Student.cpp StudentManager.cpp
HEADERS = Student.h StudentManager.h

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Default target
all: $(TARGET)

# Link object files to create executable
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Compile source files to object files
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build files
clean:
	rm -f $(OBJECTS) $(TARGET)
	rm -f students.txt

# Run the program
run: $(TARGET)
	./$(TARGET)

# Clean and rebuild
rebuild: clean all

# Debug build with debug symbols
debug: CXXFLAGS += -DDEBUG -g
debug: clean all

# Install (copy to /usr/local/bin)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/

# Uninstall
uninstall:
	sudo rm -f /usr/local/bin/$(TARGET)

.PHONY: all clean run rebuild debug install uninstall

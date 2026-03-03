CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -I./include
TARGET = university_app
SRC = src/main.cpp

all: $(TARGET)

$(TARGET): $(SRC) include/database.h include/course.h include/faculty.h include/student.h include/person.h
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run

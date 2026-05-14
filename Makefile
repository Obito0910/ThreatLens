# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall -I./include
TARGET = test_week3.exe

# Source files
SOURCES = src/Exceptions.cpp \
          src/FileSample.cpp \
          src/AnalysisResult.cpp \
          src/Analyzer.cpp \
          src/HashAnalyzer.cpp \
          src/StringAnalyzer.cpp \
          src/SignatureAnalyzer.cpp \
          src/MetadataAnalyzer.cpp \
          src/User.cpp \
          src/AnalysisEngine.cpp \
          src/Logger.cpp \
          src/ReportGenerator.cpp \
          test_week3_minimal.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)

# Build target
all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del /Q src\*.o test_week3_minimal.o $(TARGET) 2>nul

run: $(TARGET)
	.\$(TARGET)

.PHONY: all clean run
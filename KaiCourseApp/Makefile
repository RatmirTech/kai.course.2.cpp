\
# Makefile for KaiCourseApp using MSVC (cl.exe)
# Intended for use with nmake.exe

# Compiler and flags
CXX = cl.exe
# /nologo: Suppress copyright message
# /EHsc: Enable C++ exception handling (synchronous)
# /Zi: Enable debugging information (generates PDB)
# /std:c++17: Use C++17 standard
# /W4: Warning level 4 (recommended)
CXXFLAGS = /nologo /EHsc /Zi /std:c++17 /W4

# LDFLAGS for the linker
# /nologo: Suppress copyright message
# /DEBUG: Generate debug information for the executable
LDFLAGS = /nologo /DEBUG

# Target executable
TARGET = KaiCourseApp.exe

# Source files
SRCS = KaiCourseApp.cpp GasCompany.cpp

# Object files (derived from source files)
OBJS = $(SRCS:.cpp=.obj)

# Header files - for explicit dependency listing
# If any of these headers change, the corresponding .obj files will be recompiled.
HDRS = GasCompany.h GasPump.h GasStation.h PriorityQueue.h Storage.h

# Default target: build all
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	@echo Linking $@...
	$(CXX) $(LDFLAGS) $(OBJS) /Fe$(TARGET)
	@echo Build of $(TARGET) complete.

# Explicit rules for compiling each source file.
# $< refers to the first prerequisite (the .cpp file).
# $@ refers to the target (the .obj file).

KaiCourseApp.obj: KaiCourseApp.cpp $(HDRS)
	@echo Compiling $<...
	$(CXX) $(CXXFLAGS) /c $< /Fo$@

GasCompany.obj: GasCompany.cpp $(HDRS)
	@echo Compiling $<...
	$(CXX) $(CXXFLAGS) /c $< /Fo$@

# Phony target for cleaning up build files
.PHONY: clean
clean:
	@echo Cleaning up project files...
	-del /Q /F $(OBJS) $(TARGET) *.pdb *.ilk vc*.idb 2>nul
	@echo Clean complete.


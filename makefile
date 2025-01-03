# https://stackoverflow.com/questions/30573481/how-to-write-a-makefile-with-separate-source-and-header-directories
# g++ options:
# -g: debug info
# -o: output
# -c: compile

CC = g++

SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin
SHDR_DIR = $(BIN_DIR)/shaders

TARGET := $(BIN_DIR)/main
SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC))

# CPP: (C) (P)re(P)rocessor
# -I Preprossessor flag
CPPFLAGS = -Iinclude -MMD -MD 
# Some warnings about bad code
CFLAGS = -Wall -g
# -L Linker flag
# Disable if no lib/ directory
LDFLAGS = -Llib
LDLIBS = -lm

# OPENGL flags
OPENGL_FLAGS= \
			  -lGL\
			  -lX11\
			  -lpthread\
			  -lXrandr\
			  -lXi\
			  -ldl\
			  -lGLESv2\
			  `pkg-config --static --libs glfw3`
			  #-lglfw3

.PHONY : all clean # Makes sure no all file is built

# default target
all : $(TARGET) 
	@echo Compile $(SRC)
	@echo Build $(OBJ)
	@echo Target $(TARGET)
	cp -rv shaders/ $(SHDR_DIR)

# Build OBJ files
$(TARGET) : $(OBJ) | $(BIN_DIR)
	@echo Building OBJ files
	$(CC) $(OPENGL_FLAGS) $(LDFLAGS) $^ $(LDLIBS) -o $@


# Compiles .cpp files
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	@echo Compiling .cpp files
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# Creates bin/ if it doesnt exist
$(BIN_DIR) $(OBJ_DIR) $(SHDR_DIR):
	mkdir -p $@

clean : $(BIN_DIR) $(OBJ_DIR)
	rm -rv $(BIN_DIR) $(OBJ_DIR)

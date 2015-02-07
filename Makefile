NVCC = nvcc
NVCC_OPTS =-Xcompiler -Wextra -m64
CC = g++
GCC_OPTS =
EXEC = executables/vim_smile_plugin
LOADER = executables/load_model

SRC_DIR = src
OBJ_DIR = obj
INCLUDE_DIR = include
LIB_DIR = lib

OPENCV_LIBPATH =/opt/local/lib
OPENCV_INCLUDEPATH =/opt/local/include
OPENCV_LIBS =-lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_video -lopencv_contrib

#Suffixes
all: $(LOADER) $(EXEC) Makefile

$(EXEC): $(OBJ_DIR)/main.o
	$(CC) -o $(EXEC) $^ -L $(OPENCV_LIBPATH) $(OPENCV_LIBS)

$(OBJ_DIR)/main.o: $(SRC_DIR)/main.cpp
	$(CC) -c $^ $(GCC_OPTS) -I $(OPENCV_INCLUDEPATH) -o $(OBJ_DIR)/main.o

$(LOADER): $(OBJ_DIR)/loader.o
	$(CC) -o $(LOADER) $^ -L $(OPENCV_LIBPATH) $(OPENCV_LIBS)

$(OBJ_DIR)/loader.o: $(SRC_DIR)/load_model.cpp
	$(CC) -c $^ $(GCC_OPTS) -I $(OPENCV_INCLUDEPATH) -o $(OBJ_DIR)/loader.o

clean:
	rm -f $(OBJ_DIR)/*.o $(EXEC) $(LOADER)

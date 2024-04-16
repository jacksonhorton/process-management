### VARIABLES

## Compiler variable
CC = g++

## Compiler Flag variable
# Compile with debugging features and all errors + warnings.
CFLAGS = -g -Wall -Wextra

## Target Flag variable
# Contains all targets to fully compile.
# !! If adding more targets, implement them in targets and add them here so they are compiled. !!
TARGET = Manager

### TARGETS

## all
all: 	$(TARGET)

## run
run:	$(TARGET) execute

## Target
# Using $(TARGET) it will link all object (*.o) files.
# Defines name of output to "stacker".
$(TARGET): 	main.o $(TARGET).o
	$(CC) $(CFLAGS) -o $(TARGET) main.o $(TARGET).o

## main.o
# Requires main.cpp and all header files.
main.o: 	main.cpp $(TARGET).h
	$(CC) $(CFLAGS) -c main.cpp

## stacker.o
# Requires stacker header and implementation files.
Manager.o: 	$(TARGET).cpp $(TARGET).h
	$(CC) $(CFLAGS) -c $(TARGET).cpp

## clean
# Removes all unnecessary files including objects (*.o) and emacs backup (*~) files.
clean:
	$(RM) $(TARGET) -f *.o *~ *.ppm


execute:
	./$(TARGET)

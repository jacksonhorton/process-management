CC = g++
CFLAGS = -g -Wall -Wextra
TARGET = Scheduler

SOURCES = main.cpp Scheduler.cpp Manager.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	rm -rf *.o $(TARGET)

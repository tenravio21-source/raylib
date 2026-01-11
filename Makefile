CC = gcc
CFLAGS = -Wall -std=c99 -Wno-missing-braces -I./raylib/include
# The -Wl,-rpath flag tells the executable where to look for .so files at runtime
LDFLAGS = -L./raylib/lib -lraylib -lm -lpthread -ldl -lrt -lX11 -Wl,-rpath,./raylib/lib

TARGET = basic_window
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

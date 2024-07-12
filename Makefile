TARGET = Lufrak
APP_DIR = app
SRC_DIR = $(APP_DIR)/src
INC_DIR = $(APP_DIR)/include
LIBS = pdcurses Ole32

SRC_FILES := $(shell find $(SRC_DIR) -name "*.c")
OBJ_FILES := $(SRC_FILES:.c=.o)
CC = gcc
CFLAGS = -I$(INC_DIR) -Wall -std=c99 -O2
LDFLAGS = $(addprefix -l, $(LIBS))

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $@ $(LDFLAGS)
	make clean

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ_FILES)

run: $(TARGET)
	./$(TARGET)
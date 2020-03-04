SOURCES 				= $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS  				= -g -Werror -Wall -Wpedantic -std=c99 -DSUPER_LOUD
CC      				= cc
TARGET  				= emu8086

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	-rm $(SOURCES)
	-rm $(TARGET)

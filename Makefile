SOURCES 				= $(patsubst %.c,%.o,$(wildcard *.c)) generated.o
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
	-rm 8086_table.txt

8086_table.txt:
	wget http://www.mlsite.net/8086/8086_table.txt --quiet

generated.c: bin/generate_map 8086_table.txt
	cat 8086_table.txt | bin/generate_map > generated.c

bin/generate_map: bin/generate_map.c
	$(CC) $(CFLAGS) bin/generate_map.c -o bin/generate_map

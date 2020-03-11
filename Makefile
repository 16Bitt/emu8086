SOURCES 				= $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS  				= -g -Werror -Wall -Wpedantic -std=c99 -DSUPER_LOUD
CC      				= cc
TARGET  				= emu8086

$(TARGET): $(SOURCES) emu8086.h
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	-rm $(SOURCES)
	-rm $(TARGET)
	-rm bin/generate_map
	-rm 8086_table.txt

8086_table.txt:
	wget http://www.mlsite.net/8086/8086_table.txt --quiet

generated.c: bin/generate_map 8086_table.txt
	# tr is used to remove the duplicate tabs that mess up parsing
	cat 8086_table.txt | tr -s '\t' | tr -d ' ' | bin/generate_map > generated.c

bin/generate_map: bin/generate_map.c
	$(CC) $(CFLAGS) bin/generate_map.c -o bin/generate_map

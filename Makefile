SOURCES 				= $(patsubst %.c,%.o,$(wildcard *.c))
CFLAGS  				= -g -Werror -Wall -Wpedantic -std=c99 -DSUPER_LOUD
CC      				= cc
TARGET  				= emu8086
INST_TABLE  		= bin/8086_table.txt
INST_URL				= http://www.mlsite.net/8086/8086_table.txt
GENERATED_FILES = generated_decode.c generated_define.h

$(TARGET): $(GENERATED_FILES) $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

$(INST_TABLE):
	echo All credit for the instruction table goes to mlsite.net!
	wget --quiet $(INST_URL) -O $(INST_TABLE)

$(GENERATED_FILES): $(INST_TABLE) bin/parse_inst.rb
	ruby bin/parse_inst.rb $(INST_TABLE) define > generated_define.h
	ruby bin/parse_inst.rb $(INST_TABLE) decode > generated_decode.c

clean:
	-rm $(GENERATED_FILES)
	-rm $(INST_TABLE)
	-rm $(SOURCES)
	-rm $(TARGET)

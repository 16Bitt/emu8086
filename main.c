#include "stdio.h"
#include "emu8086.h"

uint16_t testread(uint16_t address) {
  printf("READ VALUE %x\n", (unsigned int) address);
  return 0;
}

void testwrite(uint16_t address, uint16_t value) {
  printf("WRITE VALUE: %x AT %x\n", (unsigned int) value, (unsigned int) address);
}

int main2(int argc, char **argv) {
  struct Bus *bus = initialize_bus();
  
  struct BusMapping mapping1;
  mapping1.read = &testread;
  mapping1.write = &testwrite;
  mapping1.lower = 0;
  mapping1.upper = 100;
  
  struct BusMapping mapping2;
  mapping2.read = &testread;
  mapping2.write = &testwrite;
  mapping2.lower = 301;
  mapping2.upper = 4000;
  
  struct BusMapping mapping3;
  mapping3.read = &testread;
  mapping3.write = &testwrite;
  mapping3.lower = 101;
  mapping3.upper = 300;
  
  add_mapping(bus, &mapping2);
  add_mapping(bus, &mapping1);
  add_mapping(bus, &mapping3);
  
  int i;
  for(i = 0; i < 400; i++) {
    bus_write_byte(bus, i, i);
  } 

  return 0;
}

int main(int argc, char **argv) {
  uint8_t *buffer = load_binary("./example-asm/mov");
  if(buffer == NULL) {
    return -1;
  }

  struct Instruction inst;
  puts("mov ax, bx");
  inst_load(&inst, buffer[0], INST_LOAD_OPCODE);
  inst_load(&inst, buffer[1], INST_LOAD_ADDRESS);
  inst_dump(&inst);
  puts("mov al, bl");
  inst_load(&inst, buffer[2], INST_LOAD_OPCODE);
  inst_load(&inst, buffer[3], INST_LOAD_ADDRESS);
  inst_dump(&inst);
  puts("mov ax, 9999");
  inst_load(&inst, buffer[4], INST_LOAD_OPCODE);
  inst_load(&inst, buffer[5], INST_LOAD_ADDRESS);
  inst_dump(&inst);
  puts("cli");
  inst_load(&inst, buffer[5], INST_LOAD_OPCODE);
  inst_load(&inst, buffer[6], INST_LOAD_ADDRESS);
  inst_dump(&inst);
  puts("hlt");
  inst_load(&inst, buffer[6], INST_LOAD_OPCODE);
  inst_load(&inst, buffer[7], INST_LOAD_ADDRESS);
  inst_dump(&inst);

  free(buffer);
  return 0;
}

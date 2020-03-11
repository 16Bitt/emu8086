#include "emu8086.h"
#include "stdio.h"

void inst_dump(struct Instruction *inst) {
  printf("opcode: ");
  binary_print(inst->opcode);
  printf(" size: ");
  binary_print(inst->is_word);
  printf(" direction: ");
  binary_print(inst->direction);
  printf("\nmod:    ");
  binary_print(inst->mod);
  printf(" rm:   ");
  binary_print(inst->rm);
  printf(" reg:       ");
  binary_print(inst->reg);

  printf("\n");
}

enum inst_load_t inst_load(struct Instruction *inst, uint8_t byte, enum inst_load_t step) {
  switch(step) {
  case INST_LOAD_ADDRESS:
    return inst_address_load(inst, byte);
  case INST_LOAD_OPCODE:
  default:
    return inst_opcode_load(inst, byte);
  }
}

enum inst_load_t inst_opcode_load(struct Instruction *inst, uint8_t byte) {
  inst->is_word = byte & 1;
  inst->direction = (byte >> 1) & 1;
  inst->opcode = (byte >> 2) & 0x3f; // Binary 00111111 (lowest 6 bits)

  return INST_LOAD_ADDRESS;
}

enum inst_load_t inst_address_load(struct Instruction *inst, uint8_t byte) {
  inst->rm = byte & 0x07; // Binary 00000111 (lowest 3 bits)
  inst->reg = (byte >> 3) & 0x07;
  inst->mod = (byte >> 6) & 0x03; // Binary 00000011 (lowest 2 bits)

  if(inst->mod == RM_IMMEDIATE || inst->mod == MOD_TABLE_2_WORD || inst->mod == MOD_TABLE_2_BYTE) {
    return INST_LOAD_BYTE_1;
  }

  return INST_LOAD_DONE;
}

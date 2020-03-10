#ifndef EMU8086_H
#define EMU8086_H

#include "stdlib.h"
#include "stdint.h"
#include "stdio.h"

struct Registers {
  /* Instruction pointer */
  int16_t ip;

  /* Segment registers */
  int16_t es, cs, ss, ds;

  /* General Purpose */
  int16_t ax, bx, cx, dx;

  /* Meta registers */
  int16_t sp, bp, si, di, flags;
};

enum Flag {
  F_CARRY = (1 << 0),
  F_PARITY = (1 << 2),
  F_AUXILLARY = (1 << 4),
  F_ZERO = (1 << 6),
  F_SIGN = (1 << 7),
  F_TRAP = (1 << 8),
  F_INTERRUPT = (1 << 9),
  F_DIRECTION = (1 << 10),
  F_OVERFLOW = (1 << 11)
};

typedef uint16_t (*BusReadHandler)(uint16_t address);
typedef void (*BusWriteHandler)(uint16_t address, uint16_t value);

/* Defines the read and write rules for a section of the bus */
struct BusMapping {
  char *name;
  uint32_t lower, upper;

  BusReadHandler read;
  BusWriteHandler write;
};

/* Tree lookup for addresses on the bus */
struct BusRangeNode {
  struct BusMapping *mapping;
  struct BusRangeNode *left, *right;
};

/* Core bus for doing reads and writes from the CPU */
struct Bus {
  struct BusRangeNode *root;
};

struct Bus *initialize_bus();
int free_bus(struct Bus *bus);
int add_mapping(struct Bus *bus, struct BusMapping *mapping);
int bus_node_insert(struct BusRangeNode *current, struct BusRangeNode *target);
struct BusRangeNode *lookup_address(struct BusRangeNode *node, uint32_t address);
uint16_t bus_read_word(struct Bus *bus, uint32_t address);
uint16_t bus_read_byte(struct Bus *bus, uint32_t address);
uint16_t bus_write_word(struct Bus *bus, uint32_t address, uint16_t value);
uint16_t bus_write_byte(struct Bus *bus, uint32_t address, uint8_t value);

/* Instruction decode interface */

struct instruction {
  // Byte 1: opcode
  uint8_t opcode : 6;
  uint8_t direction : 1;
  uint8_t is_word : 1;

  // Byte 2: addressing mode
  uint8_t mod : 2;
  uint8_t reg : 3;
  uint8_t rm : 3;

  // Byte 3 - 6: instruction data
  uint8_t data_low_a;
  uint8_t data_high_a;
  uint8_t data_low_b;
  uint8_t data_high_b;
};

// direction bit modes
#define DIRECTION_REG_TO_MEM 0
#define DIRECTION_MEM_TO_REG 1
#define DIRSIGN_IMM_WORD 0
#define DIRSIGN_EXTEND_OPERAND 1

// mod bit modes
#define MOD_TABLE_1 0
#define MOD_TABLE_2_BYTE 1
#define MOD_TABLE_2_WORD 2
#define MOD_REG_TABLE 3

#define RM_IMMEDIATE 0x6

enum inst_load_t {
  INST_LOAD_OPCODE,
  INST_LOAD_ADDRESS,
  INST_LOAD_BYTE_1,
  INST_LOAD_BYTE_2,
  INST_LOAD_BYTE_3,
  INST_LOAD_BYTE_4,
  INST_LOAD_DONE
};

// instruction helpers
void inst_dump(struct instruction *inst);

// state machine entrypoint for instruction parsing
enum inst_load_t inst_load(struct instruction *inst, uint8_t byte, enum inst_load_t step);
enum inst_load_t inst_opcode_load(struct instruction *inst, uint8_t byte);
enum inst_load_t inst_address_load(struct instruction *inst, uint8_t byte);

/* Utilities */
uint8_t* load_binary(char *path);
void binary_print(uint8_t byte);

enum op_args_t {
  args_AH_Ib,
  args_AL_DX,
  args_AL_Ib,
  args_AL_Ob,
  args_BH_Ib,
  args_BL_Ib,
  args_CH_Ib,
  args_CL_Ib,
  args_DH_Ib,
  args_DL_Ib,
  args_DX_AL,
  args_DX_eAX,
  args_Eb_1,
  args_Eb_CL,
  args_Eb_Gb,
  args_Eb_Ib,
  args_Ev_1,
  args_Ev_CL,
  args_Ev_Gv,
  args_Ev_Ib,
  args_Ev_Iv,
  args_Ew_Sw,
  args_Gb_Eb,
  args_Gv_Ev,
  args_Gv_M,
  args_Gv_Mp,
  args_Ib_AL,
  args_Ib_eAX,
  args_Ob_AL,
  args_Ov_eAX,
  args_Sw_Ew,
  args_eAX_DX,
  args_eAX_Ib,
  args_eAX_Iv,
  args_eAX_Ov,
  args_eBP_Iv,
  args_eBP_eAX,
  args_eBX_Iv,
  args_eBX_eAX,
  args_eCX_Iv,
  args_eCX_eAX,
  args_eDI_Iv,
  args_eDI_eAX,
  args_eDX_Iv,
  args_eDX_eAX,
  args_eSI_Iv,
  args_eSI_eAX,
  args_eSP_Iv,
  args_eSP_eAX
};

/* Linker hacks! Why is this needed? */
int fileno(FILE *f);

#endif

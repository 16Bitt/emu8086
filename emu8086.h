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

struct Instruction {
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
void inst_dump(struct Instruction *inst);

// state machine entrypoint for instruction parsing
enum inst_load_t inst_load(struct Instruction *inst, uint8_t byte, enum inst_load_t step);
enum inst_load_t inst_opcode_load(struct Instruction *inst, uint8_t byte);
enum inst_load_t inst_address_load(struct Instruction *inst, uint8_t byte);

/* Utilities */
uint8_t* load_binary(char *path);
void binary_print(uint8_t byte);

/* Execution context */
struct ExecutionContext {
  struct Registers regs;
  struct Bus *bus;
  uint16_t fetch_addr;
};
struct ExecutionContext * mk_context();

/* Addressing modes for opcodes */
enum op_args_t {
  args_3,
  args_AH_Ib,
  args_AL_DX,
  args_AL_Ib,
  args_AL_Ob,
  args_Ap,
  args_BH_Ib,
  args_BL_Ib,
  args_CH_Ib,
  args_CL_Ib,
  args_CS,
  args_DH_Ib,
  args_DL_Ib,
  args_DS,
  args_DX_AL,
  args_DX_eAX,
  args_ES,
  args_Eb,
  args_Eb_1,
  args_Eb_CL,
  args_Eb_Gb,
  args_Eb_Ib,
  args_Ev,
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
  args_I0,
  args_Ib,
  args_Ib_AL,
  args_Ib_eAX,
  args_Iw,
  args_Jb,
  args_Jv,
  args_Ob_AL,
  args_Ov_eAX,
  args_SS,
  args_Sw_Ew,
  args_eAX,
  args_eAX_DX,
  args_eAX_Ib,
  args_eAX_Iv,
  args_eAX_Ov,
  args_eBP,
  args_eBP_Iv,
  args_eBPeAX,
  args_eBX,
  args_eBX_Iv,
  args_eBXeAX,
  args_eCX,
  args_eCX_Iv,
  args_eCXeAX,
  args_eDI,
  args_eDI_Iv,
  args_eDIeAX,
  args_eDX,
  args_eDX_Iv,
  args_eDXeAX,
  args_eSI,
  args_eSI_Iv,
  args_eSIeAX,
  args_eSP,
  args_eSP_Iv,
  args_eSPeAX,
  args_none,
};

/* Core handling loop */
void handle_decode(struct ExecutionContext *ec, uint8_t op);

/* Opcode handlers */
void op_AAA(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_AAD(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_AAM(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_AAS(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_ADC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_ADD(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_AND(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CALL(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CBW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CLC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CLD(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CLI(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CMC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CMP(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CMPSB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CMPSW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_CWD(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_DAA(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_DAS(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_DEC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP1(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP2(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP3a(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP3b(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP4(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_GRP5(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_HLT(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_IN(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_INC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_INT(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_INTO(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_IRET(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JA(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JBE(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JCXZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JG(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JGE(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JL(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JLE(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JMP(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JNB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JNO(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JNS(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JNZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JO(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JPE(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JPO(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JS(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_JZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LAHF(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LDS(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LEA(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LES(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LOCK(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LODSB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LODSW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LOOP(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LOOPNZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_LOOPZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_MOV(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_MOVSB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_MOVSW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_NOP(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_OR(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_OUT(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_POP(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_POPF(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_PUSH(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_PUSHF(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_REPNZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_REPZ(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_RET(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_RETF(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_SAHF(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_SBB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_SCASB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_SCASW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_STC(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_STD(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_STI(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_STOSB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_STOSW(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_SUB(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_TEST(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_WAIT(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_XCHG(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_XLAT(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);
void op_XOR(struct ExecutionContext *ec, uint8_t op, enum op_args_t addr_mode);

/* Linker hacks! Why is this needed? */
int fileno(FILE *f);

#endif

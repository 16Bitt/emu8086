#ifndef EMU8086_H
#define EMU8086_H

#include "stdlib.h"
#include "stdint.h"

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

/* Generated instruction file -- put in a seperate place for ease of development and size */
#include "generated_define.h"

struct instruction {
  enum operation_t op;
  enum register_mode_t mode;
};
#endif

#include "emu8086.h"

#ifdef SUPER_LOUD
#include "stdio.h"
#endif

struct Bus *initialize_bus() {
  struct Bus *bus = (struct Bus *) malloc(sizeof(struct Bus));

  return bus;
}

int add_mapping(struct Bus *bus, struct BusMapping *mapping) {
  struct BusRangeNode *node = (struct BusRangeNode *) malloc(sizeof(struct BusRangeNode));
  node->mapping = mapping;
  
  /* Simplest case -- this is the first node in the tree */
  if(bus->root == NULL) {
    bus->root = node;
    return 0;
  }
  
  return bus_node_insert(bus->root, node);
}

int bus_node_insert(struct BusRangeNode *current, struct BusRangeNode *target) {
  if(current->left != NULL && current->left->mapping->lower > target->mapping->lower) {
    return bus_node_insert(current->left, target);
  }

  if(current->right != NULL && current->right->mapping->lower < target->mapping->lower) {
    return bus_node_insert(current->right, target);
  }
 
  if(current->left == NULL && current->mapping->lower > target->mapping->lower) {
    current->left = target;
    return 0;   
  }

  if(current->right == NULL && current->mapping->lower < target->mapping->lower) {
    current->right = target;
    return 0;   
  }

  /* VERY invalid state */
  return -1;
}

struct BusRangeNode *lookup_address(struct BusRangeNode *node, uint32_t address) {
  if(node == NULL) {
#ifdef SUPER_LOUD
    printf("Could not find address 0x%x in tree!\n", address);
#endif
    return NULL;
  }

  if(address >= node->mapping->lower && address <= node->mapping->upper) {
#ifdef SUPER_LOUD
    printf("Found mapping for 0x%x: in range 0x%x - 0x%x\n", address, node->mapping->lower, node->mapping->upper);
#endif
    return node;
  }

  if(address < node->mapping->lower) {
    return lookup_address(node->left, address);
  }

  if(address > node->mapping->upper) {
    return lookup_address(node->right, address);
  }
  
  return NULL;
}

uint16_t bus_read_word(struct Bus *bus, uint32_t address) {
  struct BusRangeNode *range = lookup_address(bus->root, address);
  
  /* for the time being assume no bus mapping means we read a zero */
  if(range == NULL) {
    return 0;
  }
  
  return range->mapping->read(address);
}

uint16_t bus_read_byte(struct Bus *bus, uint32_t address) {
  struct BusRangeNode *range = lookup_address(bus->root, address);
  
  /* for the time being assume no bus mapping means we read a zero */
  if(range == NULL) {
    return 0;
  }

  uint16_t word = range->mapping->read(address);
  return (word >> 8) & 0xff; /* Take the highest (least significant) byte */
}

uint16_t bus_write_word(struct Bus *bus, uint32_t address, uint16_t value) {
  struct BusRangeNode *range = lookup_address(bus->root, address);
  
  /* for the time being assume no bus mapping means we ignore the write */
  if(range == NULL) {
    return 0;
  }

  range->mapping->write(address, value);
  return 0;
}

uint16_t bus_write_byte(struct Bus *bus, uint32_t address, uint8_t value) {
  struct BusRangeNode *range = lookup_address(bus->root, address);
  
  /* for the time being assume no bus mapping means we ignore the write */
  if(range == NULL) {
    return 0;
  }

  uint16_t existing = range->mapping->read(address);
  uint16_t masked = (((uint16_t) value) << 8) + (existing & 0xff);
  range->mapping->write(address, masked);
  return 0;
}

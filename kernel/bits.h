#ifndef __BITS_H__
#define __BITS_H__

#include "types.h"

#define MASK(X, Y) ((~(0xfffffffu << ((Y) - (X) + 1))) << (X))

// set offset0...offset1 to v exactly
static inline uint32
set_bits(uint32 i, uint32 v, uint8 offset0, uint8 offset1) {
  uint32 mask = MASK(offset0, offset1);
  return (i & ~mask) | ((v << offset0) & mask);
}

static inline uint32
set_bit(uint32 i, uint32 v, uint8 offset) {
  return set_bits(i, v, offset, offset);
}

static inline uint32
clear_bits(uint32 i, uint8 offset0, uint8 offset1) {
  return set_bits(i, 0x0, offset0, offset1);
}

static inline uint32
on_bit(uint32 i, uint8 offset) {
  return set_bit(i, 0x1, offset);
}

static inline uint32
off_bit(uint32 i, uint8 offset) {
  return set_bit(i, 0x0, offset);
}

// set offset0...offset1 to 1 when the bits in v are 1, while keep intact for the bits in v are 0.
static inline uint32
apply_bits(uint32 i, uint32 v, uint8 offset0, uint8 offset1) {
  return i | ((v << offset0) & MASK(offset0, offset1));
}

static inline uint32
apply_bit(uint32 i, uint32 v, uint8 offset) {
  return set_bits(i, v, offset, offset);
}

// this is typically used to build a value and can be combined with | with other non-overlapped bits
static inline uint32
bits(uint32 v, uint8 offset0, uint8 offset1) {
  return set_bits(0x0, v, offset0, offset1);
}

static inline uint32
bit(uint32 v, uint8 offset) {
  return set_bits(0x0, v, offset, offset);
}

static inline uint32
get_bits(uint32 i, uint8 offset0, uint8 offset1) {
  return (i & MASK(offset0, offset1)) >> offset0;
}

static inline uint32
get_bit(uint32 i, uint8 offset) {
  return get_bits(i, offset, offset);
}

#endif
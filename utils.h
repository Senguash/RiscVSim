#include <stdio.h>

//Usage: printf("Leading text "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(byte));
#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  ((byte) & 0x80 ? '1' : '0'), \
  ((byte) & 0x40 ? '1' : '0'), \
  ((byte) & 0x20 ? '1' : '0'), \
  ((byte) & 0x10 ? '1' : '0'), \
  ((byte) & 0x08 ? '1' : '0'), \
  ((byte) & 0x04 ? '1' : '0'), \
  ((byte) & 0x02 ? '1' : '0'), \
  ((byte) & 0x01 ? '1' : '0')

#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT printf
#else
#define DEBUG_PRINT(...)    /* Don't do anything in release builds */
#endif

#define WORD_TO_BINARY_PATTERN "0b %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c %c%c%c%c%c%c%c%c"
#define WORD_TO_BINARY(word)\
  ((word) & 0x80000000 ? '1' : '0'), \
  ((word) & 0x40000000 ? '1' : '0'), \
  ((word) & 0x20000000 ? '1' : '0'), \
  ((word) & 0x10000000 ? '1' : '0'), \
  ((word) & 0x08000000 ? '1' : '0'), \
  ((word) & 0x04000000 ? '1' : '0'), \
  ((word) & 0x02000000 ? '1' : '0'), \
  ((word) & 0x01000000 ? '1' : '0'), \
  ((word) & 0x800000 ? '1' : '0'), \
  ((word) & 0x400000 ? '1' : '0'), \
  ((word) & 0x200000 ? '1' : '0'), \
  ((word) & 0x100000 ? '1' : '0'), \
  ((word) & 0x080000 ? '1' : '0'), \
  ((word) & 0x040000 ? '1' : '0'), \
  ((word) & 0x020000 ? '1' : '0'), \
  ((word) & 0x010000 ? '1' : '0'), \
  ((word) & 0x8000 ? '1' : '0'), \
  ((word) & 0x4000 ? '1' : '0'), \
  ((word) & 0x2000 ? '1' : '0'), \
  ((word) & 0x1000 ? '1' : '0'), \
  ((word) & 0x0800 ? '1' : '0'), \
  ((word) & 0x0400 ? '1' : '0'), \
  ((word) & 0x0200 ? '1' : '0'), \
  ((word) & 0x0100 ? '1' : '0'), \
  ((word) & 0x80 ? '1' : '0'), \
  ((word) & 0x40 ? '1' : '0'), \
  ((word) & 0x20 ? '1' : '0'), \
  ((word) & 0x10 ? '1' : '0'), \
  ((word) & 0x08 ? '1' : '0'), \
  ((word) & 0x04 ? '1' : '0'), \
  ((word) & 0x02 ? '1' : '0'), \
  ((word) & 0x01 ? '1' : '0')


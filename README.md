# RiscVSim

# TODO LIST
1. Create system for managing memory (PC counter, load/store)
2. Read and write file
3. Instruction decoder
4. Implement instructions
5. Simulated system calls (steal from ripes)
6. Simulate registers 32 x 32 bit (include binary dump reg)


note:
memMan is mad on littel endian

8  7  6  5  4  3  2  1    16 15 14 13 12 11 10 9    24 23 22 21 20 19 18 17   32 31 30 29 28 27 26 25 littel endian
32 31 30 29 28 27 26 25   24 23 22 21 20 19 18 17   16 15 14 13 12 11 10 9    8  7  6  5  4  3  2  1  big endina
main:
# Demo 1: simple visual register-write demo
# Writes a distinct value into every other register in a clean, easy-to-read pattern.
# Expected nonzero registers at end:
# R8=1, R10=3, R12=5, R14=7, R16=9, R18=11, R20=13, R22=15

ADDI $t0 $zero 1      # R8  = 1
ADDI $t2 $zero 3      # R10 = 3
ADDI $t4 $zero 5      # R12 = 5
ADDI $t6 $zero 7      # R14 = 7
ADDI $s0 $zero 9      # R16 = 9
ADDI $s2 $zero 11     # R18 = 11
ADDI $s4 $zero 13     # R20 = 13
ADDI $s6 $zero 15     # R22 = 15
NOP

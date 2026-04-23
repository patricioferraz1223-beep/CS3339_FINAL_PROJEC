main:
ADDI $t0 $zero 5
NOP
NOP
NOP
ADDI $t1 $zero 5
NOP
NOP
NOP
BEQ  $t0 $t1 equal
NOP
ADDI $t2 $zero 99
NOP
NOP
NOP
equal:
ADDI $t3 $zero 1
NOP
NOP
NOP
main:

ADDI $t0 $zero 1
ADDI $t1 $zero 6
ADDI $t2 $zero 0
NOP
NOP
NOP

loop:
ADD  $t2 $t2 $t0     
ADDI $t0 $t0 1        
NOP
NOP
NOP
BEQ  $t0 $t1 done     
NOP
BEQ  $t0 $t0 loop     
NOP

done:
ADD  $s0 $t2 $zero
NOP
NOP
NOP
ADDI $s2, $zero, 0x1001  # s2 now holds 0x1001
NOP
NOP
NOP
SLL  $s2, $s2, 16        # $s2 is now 0x10010000
NOP
NOP
NOP
SW   $s0, 8($s2)         # Stores in 0x10010008
NOP
NOP
NOP
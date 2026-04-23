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
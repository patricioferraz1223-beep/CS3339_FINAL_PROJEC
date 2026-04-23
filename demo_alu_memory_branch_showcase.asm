main:
ADDI $t0 $zero 10
ADDI $t1 $zero 3
NOP
NOP
NOP

ADD  $t2 $t0 $t1
SUB  $t3 $t0 $t1
MUL  $t4 $t0 $t1
AND  $t5 $t0 $t1
OR   $t6 $t0 $t1
SLL  $t7 $t1 2
SRL  $s0 $t0 1

SW   $t2 0($sp)
LW   $s1 0($sp)
NOP
NOP
NOP

ADDI $s2 $zero 0        
NOP
NOP
NOP

BEQ  $s1 $t2 success
NOP
J    done
NOP

success:
ADDI $s2 $zero 1
NOP
NOP
NOP

done:
NOP
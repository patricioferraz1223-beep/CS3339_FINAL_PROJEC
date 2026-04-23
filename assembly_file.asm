main:
ADDI $t0 $zero 10
ADDI $t1 $zero 3
ADD  $t2 $t0 $t1
SUB  $t3 $t0 $t1
MUL  $t4 $t0 $t1
AND  $t5 $t0 $t1
OR   $t6 $t0 $t1
SLL  $t7 $t1 2
SRL  $s0 $t0 1
SW   $t2 0($sp)
LW   $s1 0($sp)
BEQ  $s1 $t2 equal_label
NOP
J    end_label
equal_label:
ADDI $s2 $zero 1
start:
ADDI $t0 $zero 1
BEQ  $t0 $t0 start
NOP
end_label:
NOP
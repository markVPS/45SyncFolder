movimm r0, 0               @ 0
movimm r1, 30              @ 1 - we want to go until 2^30
movimm r2, 10              @ 2 - r2 holds the '\n' character code
movimm r3, 1               @ 3 - r3 holds the powers of 2

@ only keep printing if r0 <= r1
cmp r0, r1                 @ 4 - condition check
ble 7                      @ 5 - jump to the loop body
bal 12                     @ 6 - jump to the exit
printint r3                @ 7 - the loop body
printchar r2               @ 8 
addregimm r0, r0, 1        @ 9
mulregimm r3, r3, 2        @ 10
bal 4                      @ 11 - jump to the condition check

halt                       @ 12 - the exit

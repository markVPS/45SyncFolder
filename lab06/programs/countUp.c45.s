movimm r0, 1               @ 0
movimm r1, 100             @ 1
movimm r2, 10              @ 2

@ only keep printing if r0 <= r1
cmp r0, r1                 @ 3 - condition check
ble 6                      @ 4 - jump to the loop body
bal 10                     @ 5 - jump to the exit
printint r0                @ 6 - the loop body
printchar r2               @ 7 
addregimm r0, r0, 1        @ 8
bal 3                      @ 9 - jump to the condition check

halt                       @ 10 - the exit

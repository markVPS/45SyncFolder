movimm r0, 1               @ 0
movimm r1, 100             @ 1
movimm r3, 10              @ 2
movreg r2, r3              @ 3

@ only keep printing if r0 <= r1
cmp r0, r1                 @ 4 - condition check
ble 7                      @ 5 - jump to the loop body
bal 11                     @ 6 - jump to the exit
printint r1                @ 7 - the loop body
printchar r2               @ 8 
subregimm r1, r1, 1        @ 9
bal 4                      @ 10 - jump to the condition check

halt                       @ 11 - the exit

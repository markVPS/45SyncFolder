@@ THE FOLLOWING IS SCRATCH WORK. THE ACTUAL PROGRAM IS BELOW.

@@ height = 5
@@ width = 10
@@ 
@@ // print first row
@@ for (int j = 1; j <= width; j++) {
@@   print *
@@ }
@@ print \n
@@ 
@@ // print middle rows
@@ for (int i = 1; i <= height - 2; i++) {
@@   print *
@@   for (int j = 1; j <= width - 2; j++) {
@@     print ' '
@@   }
@@   print *
@@   print \n
@@ }
@@ 
@@ // print last row
@@ for (int j = 1; j <= width; j++) {
@@   print *
@@ }
@@ print \n
@@ 
@@ ===>
@@ 
@@ mov r0, 5 @ height
@@ mov r1, 10 @ width
@@ 
@@ mov r3, 1 @ j
@@ loop1condition:
@@ cmp r3, r1
@@ ble loop1body
@@ bal loop1exit
@@ loop1body:
@@ print * using r2
@@ addregimm r3, r3, 1
@@ bal loop1condition
@@ loop1exit:
@@ print \n using r2
@@ 
@@ mov r2, 1 @ i = 1
@@ subregimm r0, r0, 2
@@ subregimm r1, r1, 2
@@ outloopcondition:
@@ cmp r2, r0 @ i < height - 2
@@ ble outerloopbody
@@ bal outloopexit
@@ outerloopbody:
@@ print * using r3
@@ 
@@ mov r3, 1 @ j = 1
@@ innerloopcondition:
@@ cmp r3, r1
@@ ble innerloopbody
@@ bal innerloopexit
@@ innerloopbody:
@@ save r3 at address 255
@@ movimm r3, ' '
@@ printchar r3
@@ load r3 from address 255
@@ addregimm r3, r3, 1
@@ innerloopexit:
@@ 
@@ print * using r3
@@ print \n using r3
@@ addregimm r2, r2, 1
@@ outerloopexit:
@@ 
@@ addregimm r1, r1, 2 @ reset width
@@ 
@@ mov r3, 1 @ j
@@ loop2condition:
@@ cmp r3, r1
@@ ble loop2body
@@ bal loop2exit
@@ loop2body:
@@ print * using r2
@@ addregimm r3, r3, 1
@@ bal loop2condition
@@ loop2exit:
@@ print \n using r2
@@ 
@@ halt
@@ 
@@ ===>

@@ THE ACTUAL PROGRAM BEGINS HERE:

movimm r0, 24 @ height of box        @ 0
movimm r1, 42 @ width of box          @ 1

movimm r3, 1  @ j                    @ 2
@ loop1condition:
cmp r3, r1                           @ 3
ble 6                                @ 4 - branch to loop1body
bal 10                               @ 5 - branch to loop1exit
@ loop1body:
movimm r2, 42                        @ 6
printchar r2                         @ 7
addregimm r3, r3, 1                  @ 8
bal 3                                @ 9 - branch to loop1condition
@ loop1exit:
movimm r2, 10                        @ 10
printchar r2                         @ 11

movimm r2, 1 @ i = 1                 @ 12
subregimm r0, r0, 2                  @ 13
subregimm r1, r1, 2                  @ 14
@ outloopcondition:
cmp r2, r0 @ i < height - 2          @ 15
ble 18                               @ 16 - b to outerloopbody
bal 36                               @ 17 - b to outerloopexit
@ outerloopbody:
movimm r3, 42                        @ 18
printchar r3                         @ 19

movimm r3, 1 @ j = 1                 @ 20
@ innerloopcondition:
cmp r3, r1                           @ 21
ble 24                               @ 22 - b to innerloopbody
bal 30                               @ 23 - b to innerloopexit
@ innerloopbody:
store r3, 255                        @ 24
movimm r3, 32                        @ 25
printchar r3                         @ 26
load r3, 255                         @ 27
addregimm r3, r3, 1                  @ 28
bal 21                               @ 29 - b to innerloopcondition
@ innerloopexit:

movimm r3, 42                        @ 30
printchar r3                         @ 31
movimm r3, 10                        @ 32
printchar r3                         @ 33
addregimm r2, r2, 1                  @ 34
bal 15                               @ 35 - b to outerloopcondition
@ outerloopexit:

addregimm r1, r1, 2 @ reset width    @ 36

movimm r3, 1 @ j                     @ 37
@ loop2condition:
cmp r3, r1                           @ 38
ble 41                               @ 39 - b to loop2body
bal 45                               @ 40 - b to loop2exit
@ loop2body:
movimm r2, 42                        @ 41
printchar r2                         @ 42
addregimm r3, r3, 1                  @ 43
bal 38                               @ 44 - b to loop2condition
@ loop2exit:
movimm r2, 10                        @ 45
printchar r2                         @ 46

halt                                 @ 47

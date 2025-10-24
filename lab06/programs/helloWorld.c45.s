@ prints "Hello, world!\n" to the screen

@ put the string into memory for no reason
movimm r0, 72
store r0, 42
movimm r0, 101
store r0, 43
movimm r0, 108
store r0, 44
movimm r0, 108
store r0, 45
movimm r0, 111
store r0, 46
movimm r0, 44
store r0, 47
movimm r0, 32
store r0, 48
movimm r0, 119
store r0, 49
movimm r0, 111
store r0, 50
movimm r0, 114
store r0, 51
movimm r0, 108
store r0, 52
movimm r0, 100
store r0, 53
movimm r0, 33
store r0, 54
movimm r0, 10
store r0, 55

@ load it one char at a time
load r1, 42
printchar r1
load r1, 43
printchar r1
load r1, 44
printchar r1
load r1, 45
printchar r1
load r1, 46
printchar r1
load r1, 47
printchar r1
load r1, 48
printchar r1
load r1, 49
printchar r1
load r1, 50
printchar r1
load r1, 51
printchar r1
load r1, 52
printchar r1
load r1, 53
printchar r1
load r1, 54
printchar r1
load r1, 55
printchar r1

@ that's all, folks
halt

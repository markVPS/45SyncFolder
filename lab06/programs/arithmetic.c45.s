@ addreg test
movimm r0, 8
movimm r1, 6
addreg r2, r0, r1
addreg r3, r2, r0
printint r3
movimm r0, 10
printchar r0

@ addregimm test
movimm r2, 7
movimm r3, 5
addregimm r0, r3, 42
addreg r1, r0, r2
printint r1
movimm r0, 10
printchar r0

@ subreg test
movimm r0, 3
movimm r1, 0
subreg r2, r0, r1
subreg r3, r2, r0
printint r3
movimm r0, 10
printchar r0

@ subregimm test
movimm r2, 9
movimm r3, 8
subregimm r0, r3, 42
subreg r1, r0, r2
printint r1
movimm r0, 10
printchar r0

@ mulreg test
movimm r0, 6
movimm r1, 7
mulreg r2, r0, r1
mulreg r3, r2, r0
printint r3
movimm r0, 10
printchar r0

@ mulregimm test
movimm r2, 5
movimm r3, 3
mulregimm r0, r3, 42
mulreg r1, r0, r2
printint r1
movimm r0, 10
printchar r0

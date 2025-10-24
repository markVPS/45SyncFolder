.global _start //_start is a global start
_start:
    mov w0, #87 //w0=87
    mov w1, #25
    mov w5, #2
    mov w2, #7
    mov w3, #3

    add w6, w0, w1 //w6 = w0 + w1
    //add w6, w0, #30 //w6 = w0 + 30
    //You can use immediate numbers in arithmetic as well, as seen in 30
    sub w2, w2, w3 //w2 = w2 - w3
    //udiv is unsigned and sdiv is signed div
    udiv w4, w4, w2 //w4 = w4 / w2 (unsigned)

    mov w0, w4 //move the value to return in register w0

    mov x8, #93 //Exit code #83 for system call
    svc #0 //Communicates with the linux kernel to execute the system call

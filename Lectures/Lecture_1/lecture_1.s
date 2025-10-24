.global _start
_start:
    /*this is a
    multi-line comment*/
    mov w0, #42
    mov x8, #93 //93 is the code for the exit system call
    svc #0 //Tells kernel to execute the system call on the previous line


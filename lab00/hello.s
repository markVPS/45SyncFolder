.global _start
_start:
  // FIΧМЕ: write a program that outputs the string:
  // "Hello, world! I am ready for CSCI 45!" followed by a newline.
// Your program should exit with an exit code of 0.

  mov x8, #64           // syscall number for write
  mov w0, #1            // file descriptor 1 (stdout)
  ldr x1, =hello_string // load address of the string
  mov x2, #38           // length of the string
  svc #0                // makes the syscall

  mov x8, #93           // syscall number for exit
  mov w0, #0            // exit code 0
  svc #0                // make the syscall

.data
// FIΧМЕ: you should put something here
hello_string: .ascii "Hello, world! I am ready for CSCI 45!\n"


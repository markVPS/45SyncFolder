.global _start
_start:
  mov x0, #2
  mov x1, #3
  mov x2, #4

  // Don't worry about the following chunk of instructions. You're not
  // supposed to understand them yet.
  add x3, x0, x1
  sub x3, x3, x2
  mul x4, x3, x1
  mov x3, x4
  mul x4, x3, x0
  mov x3, x4
  lsl x3, x3, #4

  // TODO: set a breakpoint at _start and step through all the
  // instructions. What is the final value of x3 at this line? By
  // watching how the register values change, can you guess what the
  // previous lines are doing?

  mov w0, #0
  mov x8, #93
  svc #0

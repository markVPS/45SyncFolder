.global main
.type main, %function

// head.s — print the first 10 lines of the file in argv[1]
// Uses C stdio: fopen, fgetc, putchar, fclose
// Target: AArch64 (arm64) System V ABI

.section .rodata
mode_r:
  .asciz "r"

.text
main:
  // Prologue
  stp x29, x30, [sp, -16]!
  mov x29, sp

  // argv[1] is at [x1, 8]
  ldr x0, [x1, 8]        // x0 = filename (char *)
  cbz x0, no_file        // if no argv[1], exit nonzero
  ldr x1, =mode_r        // x1 = "r"
  bl fopen               // fopen(argv[1], "r")
  cbz x0, open_fail      // if fopen failed, exit nonzero
  mov x19, x0            // save FILE * in x19

  // Initialize line counter = 0
  mov w20, #0            // w20 = lines
  
read_loop:
  mov x0, x19            // arg: FILE *
  bl fgetc               // int c = fgetc(file)
  mov w21, w0            // w21 = c
  cmp w21, #-1           // EOF?
  beq finish             // if EOF, done (prints whole file if <10 lines)

  // echo character
  mov w0, w21
  bl putchar

  // if newline, increment line counter
  cmp w21, #10           // '\n'
  bne read_loop
  add w20, w20, #1
  cmp w20, #10
  blt read_loop          // keep going until 10 lines printed
  b finish               // printed 10 lines -> finish

finish:
  mov x0, x19
  bl fclose
  mov w0, #0
  ldp x29, x30, [sp], 16
  ret

open_fail:
no_file:
  mov w0, #1
  ldp x29, x30, [sp], 16
  ret


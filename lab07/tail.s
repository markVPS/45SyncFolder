.global main
.type main, %function

// tail.s — print the last 10 lines of the file in argv[1]
// Strategy: first pass counts '\n'; rewind; second pass skips
// max(total_lines - 10, 0) newlines, then prints to EOF.
// Uses C stdio: fopen, fgetc, putchar, rewind, fclose
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
  ldr x1, =mode_r        // x1 = "r"
  bl fopen               // fopen(argv[1], "r")
  mov x19, x0            // save FILE * in x19

  // -------- First pass: count total number of '\n' --------
  mov w20, #0            // w20 = total_lines
1:                        // count loop
  mov x0, x19
  bl fgetc               // int c = fgetc(file)
  mov w21, w0            // w21 = c
  cmp w21, #-1           // EOF?
  beq 2f                 // yes -> compute skip
  cmp w21, #10           // '\n'?
  bne 1b
  add w20, w20, #1       // total_lines++
  b 1b

2:  // compute skip = max(total_lines - 10, 0)
  mov x0, x19
  bl rewind              // rewind(file)

  mov w22, w20           // w22 = total_lines
  subs w22, w22, #10     // w22 = total_lines - 10; sets flags
  csel w22, wzr, w22, le // if <= 0, w22 = 0; else keep (skip count)

  // -------- Second pass A: skip 'skip' newlines --------
  cbz w22, 4f            // if skip == 0, start printing from beginning
3:                        // skipping loop
  mov x0, x19
  bl fgetc               // c = fgetc(file)
  mov w21, w0
  cmp w21, #-1           // EOF safety
  beq 5f                 // EOF reached unexpectedly
  cmp w21, #10           // newline?
  bne 3b
  subs w22, w22, #1      // if newline, skip--
  bgt 3b                 // keep skipping until skip == 0

  // Positioned just after the skipped newline(s).
  // Next fgetc will read the first byte to print.

4: // -------- Second pass B: print to EOF --------
  mov x0, x19
  bl fgetc               // c = fgetc(file)
  mov w21, w0
  cmp w21, #-1
  beq 5f
  mov w0, w21
  bl putchar
  b 4b

5: // close and return
  mov x0, x19
  bl fclose
  mov w0, #0
  ldp x29, x30, [sp], 16
  ret


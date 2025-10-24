.global main
.type main, %function
main:
  sub sp, sp, #16
  str lr, [sp]

  // List of arm64 syscalls: https://gpages.juszkiewicz.com.pl/syscalls-table/syscalls.html

  // FIΧМЕ: call the "getuid" syscall (not getuid32) to get your user
  mov x8, #174
  svc #0

  // printf("%u\n", uid)
  mov     w1, w0              // arg1 = uid (unsigned int)
  adrp    x0, fmt             // arg0 = &"%u\n"  (PIE-safe)
  add     x0, x0, :lo12:fmt
  bl      printf
  // ID (every user account on a Linux system has an ID). The syscall
  // takes no parameters and returns a 4-byte value in the w0 register.

  // FIΧМЕ: Print the user ID that you get back as an unsigned integer
  // value using printf and the %u specifier (instead of %d). Print a
  // newline too. That's all you need to do for this program--now
  // you're done!

  // You can use `echo $UID` or `id` on the terminal to confirm that
  // the number you print is correct.

  // return 0
  mov w0, #0
  ldr lr, [sp]
  add sp, sp, #16
  ret

  .section .rodata
fmt:
  .asciz "%u\n"

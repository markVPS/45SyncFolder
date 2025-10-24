    .text
    .global main
    .type   main, %function
    .extern printf

main:
    // prologue
    sub     sp, sp, #16
    str     lr, [sp]

    // gettimeofday(&tv, NULL)
    adrp    x20, tv
    add     x20, x20, :lo12:tv   // x20 = &tv
    mov     x0, x20              // arg0 = tv
    mov     x1, xzr              // arg1 = tz = NULL
    mov     x8, #169             // __NR_gettimeofday (AArch64)
    svc     #0

    // printf("%lu\n", tv.tv_sec)
    ldr     x1, [x20]            // x1 = tv_sec (unsigned long)
    adrp    x0, fmt
    add     x0, x0, :lo12:fmt
    bl      printf

    // return 0
    mov     w0, #0
    ldr     lr, [sp]
    add     sp, sp, #16
    ret

    .section .data
    .balign 8
tv:
    .space  16                   // struct timeval: 16 bytes (tv_sec, tv_usec)

    .section .rodata
fmt:
    .asciz  "%lu\n"


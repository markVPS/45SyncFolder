   // Minimal working pow.s for ARM64
.text
.global main

main:
    // Save registers
    stp x29, x30, [sp, #-32]!
    mov x29, sp
    
    // Read two integers
    ldr x0, =scanf_fmt
    add x1, sp, #16     // store n at sp+16
    add x2, sp, #20     // store m at sp+20  
    bl scanf
    
    // Load n and m
    ldr w0, [sp, #16]   // n
    ldr w1, [sp, #20]   // m
    
    // Simple power calculation
    mov w2, #1          // result = 1
    cmp w1, #0
    beq print_result    // if m==0, result is 1
    
power_loop:
    mul w2, w2, w0      // result *= n
    subs w1, w1, #1     // m--
    bne power_loop      // if m != 0, continue
    
print_result:
    // Print the result
    ldr x0, =printf_fmt
    mov w1, w2
    bl printf
    
    // Exit
    mov w0, #0
    ldp x29, x30, [sp], #32
    ret

.data
scanf_fmt:  .asciz "%d %d"
printf_fmt: .asciz "%d\n"

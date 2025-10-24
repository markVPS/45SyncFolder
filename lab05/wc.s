    .text
    .global main
    .type   main, %function
main:
    // Create a small frame; save LR + callee-saved we use (x19,x20).
    sub     sp, sp, #32
    str     lr, [sp]
    stp     x19, x20, [sp, #16]

    // x19 = words (w19), x20 = state (w20): 0=OUTSIDE, 1=INSIDE
    mov     w19, #0
    mov     w20, #0

.L_loop:
    bl      getchar                  // w0 = next char, or -1 on EOF

    // Check for EOF == -1 (full 32-bit -1). Use MVN to synthesize -1.
    mvn     w2, wzr                  // w2 = 0xFFFFFFFF (-1)
    cmp     w0, w2
    beq     .L_done

    // Ask: isspace(c) ?  (isspace returns 0 for false, non-zero for true)
    // Pass the char in w0; result returns in w0.
    bl      isspace
    cmp     w0, #0
    b.ne    .L_space                 // non-zero => it's a space

    // Non-space char:
    // If we were OUTSIDE, we just began a new word: words++ and go INSIDE.
    cmp     w20, #0
    b.ne    .L_continue              // already INSIDE
    add     w19, w19, #1             // words++
    mov     w20, #1                  // now INSIDE
    b       .L_continue

.L_space:
    // Any space char puts us OUTSIDE a word.
    mov     w20, #0

.L_continue:
    b       .L_loop

.L_done:
    // Print word count using "%d\n"
    ldr     x0, =int_printf
    mov     w1, w19
    bl      printf

    // Epilogue
    ldp     x19, x20, [sp, #16]
    ldr     lr, [sp]
    add     sp, sp, #32
    mov     w0, #0
    ret

    .data
int_printf:  .asciz "%d\n"


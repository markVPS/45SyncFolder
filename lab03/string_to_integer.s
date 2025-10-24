// string_to_integer.s  (ARMv8-A / AArch64)

    .global string_to_integer
    .type   string_to_integer, %function

// int string_to_integer(const char* s)
// s in x0, return in w0
string_to_integer:
    mov     w1, #0          // accumulator
    mov     w3, #10         // constant 10

1:  ldrb    w2, [x0]        // load current char
    cbz     w2, 2f          // stop at '\0'
    sub     w2, w2, #48     // ASCII '0' -> 0
    mul     w1, w1, w3      // acc *= 10
    add     w1, w1, w2      // acc += digit
    add     x0, x0, #1      // advance
    b       1b

2:  mov     w0, w1          // return acc
    ret


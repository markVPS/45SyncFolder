.global Point3D_add
Point3D_add:
    // Save callee-saved registers
    push {r4-r8, lr}
    
    // r0 = first Point3D*, r1 = second Point3D*
    mov r4, r0      // Save first pointer
    mov r5, r1      // Save second pointer
    
    // Allocate memory for new Point3D (12 bytes)
    mov r0, #12
    bl malloc
    mov r6, r0      // Save pointer to new Point3D
    
    // Load x values and add them
    ldr r7, [r4]    // x1
    ldr r8, [r5]    // x2
    add r7, r7, r8  // x1 + x2
    str r7, [r6]    // Store result x
    
    // Load y values and add them
    ldr r7, [r4, #4]  // y1 (offset 4 bytes)
    ldr r8, [r5, #4]  // y2 (offset 4 bytes)
    add r7, r7, r8    // y1 + y2
    str r7, [r6, #4]  // Store result y
    
    // Load z values and add them
    ldr r7, [r4, #8]  // z1 (offset 8 bytes)
    ldr r8, [r5, #8]  // z2 (offset 8 bytes)
    add r7, r7, r8    // z1 + z2
    str r7, [r6, #8]  // Store result z
    
    // Return pointer to new Point3D in r0
    mov r0, r6
    
    // Restore registers and return
    pop {r4-r8, pc}

.data
# not used data
HELLO: .ascii "hello, world\n"
LENGTH: .word 13
.text
memcpy_aligned_large:
    addi   $t7, $a2, -4
    blez   $t7, memcpy_bytes
    lw     $t0, 0($a1)
    sw     $t0, 0($a0)
    addi   $a2, $a2, -4
    addiu  $a1, $a1, 4
    addiu  $a0, $a0, 4
    j      memcpy_aligned_large
memcpy_bytes:
    beq    $a2, $zero, memcpy_return
    lbu    $t0, 0($a1)
    sb     $t0, 0($a0)
    addi   $a2, $a2, -1
    addiu  $a1, $a1, 1
    addiu  $a0, $a0, 1
    j      memcpy_bytes
memcpy_return:
    jr     $ra
memcpy:
    addi   $t7, $a2, -4
    blez   $t7, memcpy_bytes
    xor    $t8, $a0, $a1
    andi   $t8, $t8, 3
    subu   $t1, $zero, $a0
    andi   $t1, $t1, 3
memcpy_prepare:
    beq    $t1, $zero, memcpy_check
    lbu    $t0, 0($a1)
    sb     $t0, 0($a0)
    addi   $a2, $a2, -1
    addi   $t1, $t1, -1
    addiu  $a1, $a1, 1
    addiu  $a0, $a0, 1
    j      memcpy_prepare
memcpy_check:
    beq    $t8, $zero, memcpy_aligned_large
memcpy_unaligned_large:
    addi   $t7, $a2, -4
    blez   $t7, memcpy_bytes
    lwl    $t0, 0($a1)
    lwr    $t0, 1($a1)
    sw     $t0, 0($a0)
    addi   $a2, $a2, -4
    addiu  $a1, $a1, 4
    addiu  $a0, $a0, 4
    j      memcpy_unaligned_large

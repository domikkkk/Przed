.eqv     print_string    4
.eqv    terminate_program    10
    .data
test1:            .asciz "Ala Ma Kota\n"
ans:	.space 100

    .text
# ============================================================================
main:
    li a7, print_string
    la a0, test1
    ecall
    li t3, ' '
    la t1, ans
    la a0, test1

modify_string_loop_1:
    lbu t0, (a0)
    addi a0, a0, 2
    addi t1, t1, 1
    blt t0, t3, before_loop_2
    sb t0, -1(t1)
    b modify_string_loop_1

before_loop_2:
    addi t1, t1, -1
    la a0, test1
    addi a0, a0, 1

modify_string_loop_2:
    lbu t0, (a0)
    addi a0, a0, 2
    addi t1, t1, 1
    blt t0, t3, Exit
    sb t0, -1(t1)
    b modify_string_loop_2

Exit:
    la a0, ans
    li a7, print_string
    ecall
    li a7, terminate_program
    ecall
    
# ============================================================================
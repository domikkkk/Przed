.eqv     print_string    4
.eqv    terminate_program    10
    .data
test2:            .asciz "Ala Ma Kota\n"
test1:	.asciz "Wind On The Hill\n"
koniec_linii:	.asciz "\n"
ans:	.space 100

    .text
# ============================================================================
main:
    li a7, print_string
    la a0, test1
    ecall
    li t3, ' '
    li t4, 0
    la a0, test1
    la t1, ans

modify_string_loop_1:
    lbu t0, (a0)
    blt t0, t3, modify_string_loop_2
    addi a0, a0, 1
    addi t4, t4, 1
    b modify_string_loop_1

modify_string_loop_2:
    addi a0, a0, -1
    lbu t0, (a0)
    addi t1, t1, 1
    blt t0, t3, Exit
    sb t0, -1(t1)
    b modify_string_loop_2

Exit:
    mv a0, t4
    li a7, 1
    ecall
    la a0, koniec_linii
    li a7, print_string
    ecall
    la a0, ans
    ecall
    li a7, terminate_program
    ecall
    
# ============================================================================
.eqv     print_string    4
.eqv    terminate_program    10
    .data
test2:  .asciz "Ala Ma Kota\n"
test1:	.asciz "ala123ma3225sd\n"
koniec_linii:	.asciz "\n"
ans:	.space 100

    .text
# ============================================================================
main:
    li a7, print_string
    la a0, test1
    ecall
    li t1, '0'
    li t2, '9'
    li t3, ' '
    la t6, ans

modify_string_loop:
    lbu t4, (a0)
    blt t4, t3, modify_2
    addi a0, a0, 1
    bgt t4, t2, modify_string_loop
    blt t4, t1, modify_string_loop
    sb t4, (t6)
    addi t6, t6, 1
    b modify_string_loop

modify_2:
    la a0, test1
    addi t6, t6, -1

modify_string_loop_2:
    lbu t4, (a0)
    blt t4, t3, Exit
    addi a0, a0, 1
    bgt t4, t2, modify_string_loop_2
    blt t4, t1, modify_string_loop_2
    lbu t5, (t6)
    sb t5, -1(a0)
    addi t6, t6, -1
    b modify_string_loop_2

Exit:
    li a7, 4
    la a0, test1
    ecall
    li a7, terminate_program
    ecall
    
# ============================================================================

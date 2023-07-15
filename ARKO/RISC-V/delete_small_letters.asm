.eqv     print_string    4
.eqv    terminate_program    10
    .data
test2:  .asciz "Ala Ma Kota\n"
test1:	.asciz "Flip, Flop & Fly\n"
koniec_linii:	.asciz "\n"
ans:	.space 100

    .text
# ============================================================================
main:
    li a7, print_string
    la a0, test1
    ecall
    li t1, 'a'
    li t2, 'z'
    li t4, 0
    la a0, test1
    la t6, ans

modify_string_loop:
    lbu t0, (a0)
    beqz t0, Exit
    sb t0, (t6)
    addi a0, a0, 1
    addi t6, t6, 1
    blt t0, t1, modify_string_loop
    bgt t0, t2, modify_string_loop
    addi t6, t6, -1
    addi t4, t4, 1
    b modify_string_loop

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

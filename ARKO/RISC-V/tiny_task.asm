.eqv print_int 1
.eqv print_string 4
.eqv terminate_program 10

.data
	test1: .asciz "Ala Ma Kota\n"
	ans: .space 100
	koniec_linii: .asciz "\n"

.text
	.globl change_order
	.type change_order, @function

main:
    jal change_order
    li a7, print_int
    ecall
    la a0, koniec_linii
    li a7, print_string
    ecall
    la a0, ans
    ecall

Exit:
    li a7, terminate_program
    ecall

change_order:
    li a7, print_string
    la a0, test1
    ecall
    li t3, ' '
    li t4, 0
    la a0, test1
    la t1, ans

change_order_loop_1:
    lbu t0, (a0)
    blt t0, t3, change_order_loop_2
    addi a0, a0, 1
    addi t4, t4, 1
    b change_order_loop_1

change_order_loop_2:
    addi a0, a0, -1
    lbu t0, (a0)
    addi t1, t1, 1
    blt t0, t3, Exit_change_order
    sb t0, -1(t1)
    b change_order_loop_2

Exit_change_order:
    mv a0, t4
    jr ra
    
.eqv	print_int	1
.eqv 	print_string	4
.eqv	terminate_program	10
	.data
fibbonaci:			.asciz "Fib10:\n"

	.text
# ============================================================================
main:
    li a7, print_string
    la a0, fibbonaci
    ecall
    li a1, 10
    jal fib
    li a7, print_int
    ecall

exit:	
    li 	a7, terminate_program
    ecall

	
fib:
	li t0, 0
	li t1, 0
	li t2, 1
loop:
	beq t0, a1, Exit
	addi t0, t0, 1
	mv t3, t2
	add t2, t2, t1
	mv t1, t3
	b loop
	
Exit:
	mv a0, t1
	jr ra
	
# ============================================================================
#end of file	
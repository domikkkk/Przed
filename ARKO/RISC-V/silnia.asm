.eqv	print_int	1
.eqv 	print_string	4
.eqv	terminate_program	10

	.data
silnia10:			.asciz "Silnia z 10:\n"

	.text
# ============================================================================
main:
    li a7, print_string
    la a0, silnia10	
    ecall
    li a1, 10
    jal silnia
    li a7, print_int
    ecall

exit:	
    li 	a7, terminate_program
    ecall

	
silnia:
	li t0, 0
	li t1, 1
loop:
	beq t0, a1, Exit
	addi t0, t0, 1
	mul t1, t1, t0
	b loop
	
Exit:
	mv a0, t1
	jr ra
	
# ============================================================================
#end of file	
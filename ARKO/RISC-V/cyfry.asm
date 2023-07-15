.eqv 	print_string	4
.eqv	terminate_program	10
	.data
test2:			.asciz "tel. 12384708\n"
test1:			.asciz "tel:234972349\n"

	.text
# ============================================================================
main:
    li a7, print_string
    la a0, test1
    ecall
	
modify_string:
	li t0, '0'
	li t1, '9'
	li t5, 0
	li t6, '*'
modify_string_loop:
	lbu t2, (a0)
	addi a0, a0, 1
	beqz t2, Exit
	blt t2, t0, modify_string_loop
	bgt t2, t1, modify_string_loop
	sb t6, -1(a0)
	addi t5, t5, 1
	b modify_string_loop

Exit:
	la a0, test1
	li a7, print_string
	ecall
	mv a0, t5
	li a7, 1
	ecall
	li a7, terminate_program
	ecall
	
# ============================================================================
#end of file	
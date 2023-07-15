.data
	test1:	.asciz "hiy][eg43g3 e][efdf\n"
	ans:	.space 100
.text
main:
	la a0, test1
	li a7, 4
	ecall
	jal modify
	ecall
	mv a0, t3
	li a7, 1
	ecall
	li a7, 10
	ecall


modify:
	li t0, '['
	li t1, ']'
	li t2, 0
	li t3, 0
	la t4, ans
	li a1, 1

loop:
	lbu t5, (a0)
	beqz t5, exit
	addi a0, a0, 1
	beq t5, t0, before
	sb t5, (t4)
	addi t4, t4, 1
	b loop

before:
	addi t2, t2, 1
	beq t2, a1, loop2
	addi t3, t3, 1
	sb t5, (t4)
	addi t4, t4, 1
	b loop

loop2:
	lbu t5, (a0)
	addi a0, a0, 1
	beq t5, t1, exit_loop_2
	addi t3, t3, 1
	b loop2


exit_loop_2:
	addi t3, t3, 1
	b loop


exit:
	la a0, ans
	jr ra
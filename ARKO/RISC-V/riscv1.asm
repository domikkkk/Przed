#-------------------------------------------------------------------------------
#author       : Rajmund Kozuszek
#date         : 2022.03.29
#description  : RISC-V - function modifying the input string 
#			int modify_string(char* nts_buffer);
#				changes all 'f' letters in the null terminated string to 'F'
#				returns the length of the string
#-------------------------------------------------------------------------------

.eqv	print_int	1
.eqv 	print_string	4
.eqv	terminate_program	10

	.data
test_1:	.asciz "a\n"
test_2:	.asciz "\nflip, flop and fly\n"

# ... probably some more test cases are needed

test_begin:		.asciz "\n>>>"
test_end:		.asciz "<<<\n"

# this part is just to illustrate i/o

	.text
# ============================================================================
main:
#display the input string
    li a7, print_string	#system call for print_string
    la a0, test_1	#address of string
    ecall
    li t0, ' '
    lbu t1, (a0)
    sub t1, t1, t0
    sb t1, (a0)
    ecall
    
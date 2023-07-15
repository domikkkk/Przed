.eqv	Openfile 1024
.eqv	Readfile 63
.eqv	Writefile 64
.eqv	Closefile 57


.eqv	HeaderSize 54
.eqv	Width 18
.eqv	Height 22
.eqv	max_size 230400


.eqv	img_info_header 0
.eqv	img_info_imdat 4
.eqv	img_info_lbytes 8
.eqv	img_info_width 12
.eqv	img_info_height 16
.eqv	img_info_name 20


.eqv	Rsel 255
.eqv	Gsel 100
.eqv	Bsel 100
.eqv	dist 450


	.data
img_info:	.space 24
file:		.asciz "cos1.bmp"
result:		.asciz "result.bmp"
	.align 2
dummy:	.space 2
img_header_size:	.space HeaderSize
	.align 2
img_size:	.space max_size

	.text

main:
	addi sp, sp, -20
	sw s0, 16(sp)
	sw s1, 12(sp)
	sw s2, 8(sp)
	sw s3, 4(sp)
	sw s9, (sp)
	la a0, img_info
	la t0, img_header_size
	sw t0, img_info_header(a0)
	la t0, img_size
	sw t0, img_info_imdat(a0)
	la t0, file
	sw t0, img_info_name(a0)
	jal read_bmp
#-----------------------#
	li a0, Rsel	# R
	mv t0, a0
	slli t0, t0, 8
	li a0, Gsel	# G
	or t0, t0, a0
	slli t0, t0, 8
	li a0, Bsel	# B
	or a1, t0, a0
	li a0, dist	# dist
	mul a2, a0, a0	# dist^2
#-----------------------#
	la a0, img_info
	# a0 - address img_info, a1 - RGB (sel), a2 - dist^2
	jal sepia

	la t0, result
	la a0, img_info
	sw t0, img_info_name(a0)
	jal save_bmp
	addi sp, sp, 20
	lw s0, -4(sp)
	lw s1, -8(sp)
	lw s2, -12(sp)
	lw s3, -16(sp)
	lw s9, -20(sp)
	li a7, 10
	ecall

read_bmp:
#otwieranie do odczytu
	mv t0, a0
	lw a0, img_info_name(t0)
	li a1, 0
	li a7, Openfile
	ecall
#odczyt
	mv t1, a0 # "uchwyt" do pliku
	lw a1, img_info_header(t0)
	mv t2, a1
	li a2, HeaderSize # zapis headera
	li a7, Readfile
	ecall
	lw a0, Width(t2)
	sw a0, img_info_width(t0)
	add a1, a0, a0
	add a0, a1, a0
	addi a0, a0, 3
	srai a0, a0, 2
	slli a0, a0, 2
	sw a0, img_info_lbytes(t0)
	lw a0, Height(t2)
	sw a0, img_info_height(t0)
	mv a0, t1
	la a2, img_size # zapis pikseli
	lw a1, img_info_imdat(t0)
	ecall
#zamykanie
	mv a0, t1
	li a7, Closefile
	ecall
	mv a0, zero
	jr ra
	

sepia:
	# argument: a0 - img_info, a1 - RGB (sel), a2 - dist^2
	addi sp, sp, -4
	sw ra, 0(sp)
	mv t3, a0
	mv t1, a1
	mv t2, a2
	lw t0, img_info_imdat(t3) # pointer to actual pixel
	mv s9, t0
	lw s1, img_info_height(t3)
	lw s2, img_info_lbytes(t3)
	addi s1, s1, -1

for_every_row:
	mv t0, s9
	mul s0, s2, s1
	add t0, t0, s0
	lw s0, img_info_width(t3)
	addi s0, s0, -1
	

for_every_pixel_in_row:
	mv a3, zero
	mv t6, zero
	mv t4, zero
	mv t5, zero
	lbu t4, 2(t0)	# R
	or t6, t6, t4
	slli t6, t6, 8
	li s3, 0xFF0000
	and t5, s3, t1
	srli t5, t5, 16
	sub t4, t4, t5
	mul t4, t4, t4
	add a3, a3, t4
	srli s3, s3, 8
	lbu t4, 1(t0)	# G
	or t6, t6, t4
	slli t6, t6, 8
	and t5, s3, t1
	srli t5, t5, 8
	sub t4, t4, t5
	mul t4, t4, t4
	add a3, a3, t4
	srli s3, s3, 8
	lbu t4, (t0)	# B
	or t6, t6, t4
	and t5, s3, t1
	sub t4, t4, t5
	mul t4, t4, t4
	add a3, a3, t4
	addi t0, t0, 3
	bgt a3, t2, check
	mv t5, t6
	
R:	# 393 769 189
	mv a0, t5
	li a1, 402
	li a2, 787
	li a3, 194
	jal store_color
	sb a0, -1(t0)	# new R
G:	# 349 686 168
	mv a0, t5
	li a1, 357
	li a2, 702
	li a3, 172
	jal store_color
	sb a0, -2(t0)	# new G

B:	# 272 534 131
	mv a0, t5
	li a1, 279
	li a2, 546
	li a3, 134
	jal store_color
	sb a0, -3(t0)	# new B

check:
	addi s0, s0, -1
	bge s0, zero, for_every_pixel_in_row
	addi s1, s1, -1
	bge s1, zero, for_every_row

exit:
	lw ra, 0(sp)
	addi sp, sp, 4
	mv a0, zero
	jr ra


store_color:
	mv a4, a0	# RGB actual pixel
	mv a0, zero
	li t6, 0xFF0000	# maska
	and t4, t6, a4
	srli t4, t4, 16
	mul t4, t4, a1
	add a0, a0, t4
	srli t6, t6, 8
	and t4, t6, a4
	srli t4, t4, 8
	mul t4, t4, a2
	add a0, a0, t4
	srli t6, t6, 8
	and t4, t6, a4
	mul t4, t4, a3
	add a0, a0, t4
	srli a0, a0, 10
	li t6, 255
	blt a0, t6, exit_store_color
	li a0, 255
exit_store_color:
	mv a1, zero
	mv a2, zero
	mv a3, zero
	mv a4, zero
	jr ra


	
save_bmp:
	mv t0, a0
	lw a0, img_info_name(t0)
	li a7, Openfile
	li a1, 1
	ecall
	mv t1, a0
	li a7, Writefile
	lw a1, img_info_header(t0)
	li a2, HeaderSize
	ecall
	mv a0, t1
	li a2, max_size
	lw a1, img_info_imdat(t0)
	ecall
	li a7, Closefile
	mv a0, t1
	ecall
	mv a0, zero
	jr ra
	
	
	

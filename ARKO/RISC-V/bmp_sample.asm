#-------------------------------------------------------------------------------
#author: Rajmund Kozuszek
#date : 2022.05.05
#description : example RISC V program for reading, modifying and writing a BMP file 
#-------------------------------------------------------------------------------

# for purpose of this example I define structure which will contain important
# bitmap data for image read from the bmp file. Its C definition could be:
#	struct {
#		char* filename;		// wskazanie na nazwę pliku
#		unsigned char* hdrData; // wskazanie na bufor nagłówka pliku BMP
#		unsigned char* imgData; // wskazanie na pierwszy piksel obrazu w pamięci
#		int width, height;	// szerokość i wysokość obrazu w pikselach
#		int linebytes;		// rozmiar linii (wiersza) obrazu w bajtach
#	} imgInfo;

.eqv ImgInfo_fname	0
.eqv ImgInfo_hdrdat 	4
.eqv ImgInfo_imdat	8
.eqv ImgInfo_width	12
.eqv ImgInfo_height	16
.eqv ImgInfo_lbytes	20

.eqv MAX_IMG_SIZE 	230400 # 320 x 240 x 3 (piksele) 

# more information about bmp format: https://en.wikipedia.org/wiki/BMP_file_format
.eqv BMPHeader_Size 54
.eqv BMPHeader_width 18
.eqv BMPHeader_height 22


.eqv system_OpenFile	1024
.eqv system_ReadFile	63
.eqv system_WriteFile	64
.eqv system_CloseFile	57
	.data
imgInfo: .space	24	# deskryptor obrazu

	.align 2		# wyrównanie do granicy słowa
dummy:		.space 2
bmpHeader:	.space	BMPHeader_Size

	.align 2
imgData: 	.space	MAX_IMG_SIZE

ifname:	.asciz "c:/users/domik/ARKO/RISC-V/orange_and_black.bmp"
ofname: .asciz "c:/users/domik/ARKO/RISC-V/result.bmp"

	.text
main:
	# wypełnienie deskryptora obrazu
	li s7, 150
	li s8, 180
	li s9, 210
	la a0, imgInfo 
	la t0, ifname  # �cie�ka do obrazu
	sw t0, ImgInfo_fname(a0)
	la t0, bmpHeader # header 54 bajty
	sw t0, ImgInfo_hdrdat(a0)
	la t0, imgData # obraz 230400 bajt�w
	sw t0, ImgInfo_imdat(a0)
	jal	read_bmp
	bnez a0, main_failure
	
	la a0, imgInfo
	jal invert_red

	la a0, imgInfo
	la t0, ofname
	sw t0, ImgInfo_fname(a0)
	jal save_bmp

main_failure:
	li a7, 10
	ecall

#============================================================================
# read_bmp: 
#	reads the content of a bmp file into memory
# arguments:
#	a0 - address of image descriptor structure
#		input filename pointer, header and image buffers should be set
# return value: 
#	a0 - 0 if successful, error code in other cases
read_bmp:
	mv t0, a0	# preserve imgInfo structure pointer
	
#open file
	li a7, system_OpenFile
    lw a0, ImgInfo_fname(t0)	#file name 
    li a1, 0					#flags: 0-read file
    ecall
	
	blt a0, zero, rb_error
	mv t1, a0					# save file handle for the future
	
#read header
	li a7, system_ReadFile
	lw a1, ImgInfo_hdrdat(t0)
	li a2, BMPHeader_Size
	ecall
	
#extract image information from header
	lw a0, BMPHeader_width(a1)
	sw a0, ImgInfo_width(t0)
	
	# compute line size in bytes - bmp line has to be multiple of 4
	add a2, a0, a0
	add a0, a2, a0	# pixelbytes = width * 3 
	addi a0, a0, 3
	srai a0, a0, 2
	slli a0, a0, 2	# linebytes = ((pixelbytes + 3) / 4 ) * 4
	sw a0, ImgInfo_lbytes(t0)
	
	lw a0, BMPHeader_height(a1)
	sw a0, ImgInfo_height(t0)

#read image data
	li a7, system_ReadFile
	mv a0, t1
	lw a1, ImgInfo_imdat(t0)
	li a2, MAX_IMG_SIZE
	ecall

#close file
	li a7, system_CloseFile
	mv a0, t1
    ecall
	
	mv a0, zero
	jr ra
	
rb_error:
	li a0, 1	# error opening file	
	jr ra
	
# ============================================================================
# save_bmp - saves bmp file stored in memory to a file
# arguments:
#	a0 - address of ImgInfo structure containing description of the image`
# return value: 
#	a0 - zero if successful, error code in other cases

save_bmp:
	mv t0, a0	# preserve imgInfo structure pointer
	
#open file
	li a7, system_OpenFile
    lw a0, ImgInfo_fname(t0)	#file name
    li a1, 1					#flags: 1-write file
    ecall
	
	blt a0, zero, wb_error
	mv t1, a0					# save file handle for the future
	
#write header
	li a7, system_WriteFile
	lw a1, ImgInfo_hdrdat(t0)
	li a2, BMPHeader_Size
	ecall
	
#write image data
	li a7, system_WriteFile
	mv a0, t1
	# compute image size (linebytes * height)
	lw a2, ImgInfo_lbytes(t0)
	lw a1, ImgInfo_height(t0)
	mul a2, a2, a1
	lw a1, ImgInfo_imdat(t0)
	ecall

#close file
	li a7, system_CloseFile
	mv a0, t1
    ecall
	
	mv a0, zero
	jr ra
	
wb_error:
	li a0, 2 # error writing file
	jr ra


# ============================================================================
# set_pixel - sets the color of specified pixel
#arguments:
#	a0 - address of ImgInfo image descriptor
#	a1 - x coordinate
#	a2 - y coordinate - (0,0) - bottom left corner
#	a3 - 0RGB - pixel color
#return value: none
#remarks - a0, a1, a2 values are left unchanged

set_pixel:
	lw t1, ImgInfo_lbytes(a0)
	mul t1, t1, a2  # t1 = y * linebytes
	add t0, a1, a1
	add t0, t0, a1 	# t0 = x * 3
	add t0, t0, t1  # t0 is offset of the pixel

	lw t1, ImgInfo_imdat(a0) # address of image data
	add t0, t0, t1 	# t0 is address of the pixel
	
	#set new color
	sb   s7, (t0)		#store B
	srli a3, a3, 8
	sb   s8, 1(t0)		#store G
	srli a3, a3, 8
	sb   s9, 2(t0)		#store R

	jr ra

# ============================================================================
# get_pixel- returns color of specified pixel
#arguments:
#	a0 - address of ImgInfo image descriptor
#	a1 - x coordinate
#	a2 - y coordinate - (0,0) - bottom left corner
#return value:
#	a0 - 0RGB - pixel color
#remarks: a1, a2 are preserved

get_pixel:
	lw t1, ImgInfo_lbytes(a0)
	mul t1, t1, a2  # t1 = y * linebytes
	add t0, a1, a1
	add t0, t0, a1 	# t0 = x * 3
	add t0, t0, t1  # t0 is offset of the pixel

	lw t1, ImgInfo_imdat(a0) # address of image data
	add t0, t0, t1 	# t0 is address of the pixel

	#get color
	lbu a0,(t0)		#load B
	lbu t1,1(t0)		#load G
	slli t1,t1,8
	or a0, a0, t1
	lbu t1,2(t0)		#load R
    slli t1,t1,16
	or a0, a0, t1
					
	jr ra

# ============================================================================

# ============================================================================
# invert_red - inverts red component in the input image
#arguments:
#	a0 - address of ImgInfo image descriptor
#return value:
#	none

# for (int y = imgInfo->height-1; y >= 0; --y)
#   for (int x = imgInfo->width-1; x >= 0; --x)
#   {
#     unsigned rgb = get_pixel(imgInfo, x, y);
#     rgb = (rgb & 0x0000FFFF) | (0x00FF0000 - (rgb & 0x00FF0000));
#     set_pixel(imgInfo, x, y, rgb);
#   }

invert_red:
	addi sp, sp, -8
	sw ra, 4(sp)		#push ra
	sw s1, 0(sp)		#push s1
	mv s1, a0 			#preserve imgInfo for further use
	
	lw a2, ImgInfo_height(a0)
	addi a2, a2, -1		
	
invert_line:
	lw a1, ImgInfo_width(a0)
	addi a1, a1, -1
	
invert_pixel:
	jal get_pixel
	
	lui t0, 0x00FF0
	and a3, a0, t0
	sub a3, t0, a3
	
	slli a0, a0, 16
	srli a0, a0, 16
	or a3, a3, a0
	
	mv a0, s1
	jal set_pixel
	
	addi a1, a1, -1
	bge a1, zero, invert_pixel
	
	addi a2, a2, -1
	bge a2, zero, invert_line
	
	lw s1, 0(sp)		#pop s1
	lw ra, 4(sp)		#pop ra
	addi sp, sp, 8
	jr ra

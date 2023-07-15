	section .text
	global sepija

sepija:
	push ebp
	mov ebp, esp
	push ebx
	push ecx
	push edi
	sub esp, 12
	mov eax, [ebp+28]
	mov edx, eax
	mul edx
	mov DWORD [ebp+28], eax	;dist^2
	mov eax, [ebp+8]	;width
	mov DWORD [ebp-4], eax	;remember width
for_every_row:
	dec DWORD [ebp+12]
	mov eax, DWORD [ebp-4]
	mov [ebp+8], eax
	mov edx, DWORD [ebp+12]
	mov eax, DWORD [ebp+16]
	mul edx
	mov edx, eax
	mov eax, DWORD [ebp+20]
	add eax, edx
	mov ecx, eax
	xor edx, edx
	xor eax, eax
for_every_pixel:
	xor edi, edi
	mov ebx, 0xFF0000
	and ebx, DWORD [ebp+24]
	shr ebx, 16
	movzx edx, BYTE [ecx+2]
	sub ebx, edx
	mov eax, ebx
	mul eax
	add edi, eax		;0 + (R-Rsel)^2
	mov ebx, 0xFF00
	and ebx, DWORD [ebp+24]
	shr ebx, 8
        movzx edx, BYTE [ecx+1]
	sub ebx, edx
	mov eax, ebx
	mul eax
	add edi, eax		; + (G-Gsel)^2
	mov ebx, 0xFF
	and ebx, DWORD [ebp+24]
        movzx edx, BYTE [ecx]
	sub ebx, edx
	mov eax, ebx
	mul eax
	add edi, eax		; + (B-Bsel)^2
	xor eax, eax
	cmp edi, DWORD [ebp+28]
	jae check
R:
	xor ebx, ebx
	movzx eax, BYTE [ecx+2]
	mov edx, 402
	mul edx
	add ebx, eax
	movzx eax, BYTE [ecx+1]
	mov edx, 787
	mul edx
	add ebx, eax
	movzx eax, BYTE [ecx]
	mov edx, 194
	mul edx
	add ebx, eax
	shr ebx, 10
	mov edx, 255
	cmp ebx, edx
	jb G	
	mov ebx, edx
G:
	mov BYTE [ebp-12], bl
	xor ebx, ebx
	movzx eax, BYTE [ecx+2]
        mov edx, 357
        mul edx
        add ebx, eax
        movzx eax, BYTE [ecx+1]
        mov edx, 702
        mul edx
        add ebx, eax
        movzx eax, BYTE [ecx]
        mov edx, 172
        mul edx
        add ebx, eax
        shr ebx, 10
        mov edx, 255
        cmp ebx, edx
        jb B
        mov ebx, edx
B:
	mov BYTE [ebp-13], bl
	xor ebx, ebx
	movzx eax, BYTE [ecx+2]
        mov edx, 279
        mul edx
        add ebx, eax
        movzx eax, BYTE [ecx+1]
        mov edx, 546
        mul edx
        add ebx, eax
        movzx eax, BYTE [ecx]
        mov edx, 134
        mul edx
        add ebx, eax
        shr ebx, 10
        mov edx, 255
        cmp ebx, edx
        jb set_new_pixel
        mov ebx, edx
set_new_pixel:
	mov BYTE [ebp-14], bl
	mov bl, BYTE [ebp-12]
	mov BYTE [ecx+2], bl
	mov bl, BYTE [ebp-13]
	mov BYTE [ecx+1], bl
	mov bl, BYTE [ebp-14]
	mov BYTE [ecx], bl
check:
	xor edx, edx
	mov DWORD [ebp-12], edx
	add ecx, 3
	dec DWORD [ebp+8]
	cmp [ebp+8], edx
	ja for_every_pixel 
	cmp [ebp+12], edx
	ja for_every_row
end:
	pop edi
	pop ecx
	pop ebx
	add esp, 12
	pop ebp
	ret

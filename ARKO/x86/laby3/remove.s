	section .text
	global increasing

increasing:
	push	ebp
	mov	ebp, esp
	mov	ebx, [ebp+8]
	mov	ecx, ebx
	xor	eax, eax
	mov	dl, [ebx]
	test	dl, dl
	jz	end
	inc	eax

modify:
	inc	ebx
	mov	dh, [ebx]
	test	dh, dh
	jz	end
	cmp	dh, dl
	jbe	modify
	inc	ecx
	mov	BYTE [ecx], dh
	mov	dl, dh
	inc	eax
	jmp	modify

end:
	inc	ecx
	mov	BYTE [ecx], 0
	pop	ebp
	ret

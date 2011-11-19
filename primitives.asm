	SECTION .data
flag1:	times 64 db 0
flag2:	times 64 db 0

	SECTION .text
	global bounce_s_1, bounce_s_2

bounce_s_2:
bounce_s_2_loop:
	cmp dword [flag1], 0
	je bounce_s_2_loop
	mov dword [flag1], 0
	mov dword [flag2], 1
	;; sfence
	jmp bounce_s_2_loop
	
bounce_s_1:
	xor rax, rax
	xor rdx, rdx
	rdtscp
	mov r8, rdx
	shl r8, 32
	add r8, rax

	mov rcx, 1000000
	mov dword [flag1], 1
bounce_s_1_loop:	
	cmp dword [flag2], 0
	je bounce_s_1_loop
	mov dword [flag2], 0
	mov dword [flag1], 1
	;; sfence
	loop bounce_s_1_loop
	
	xor rax, rax
	xor rdx, rdx
	rdtscp
	mov r9, rdx
	shl r9, 32
	add r9, rax
	sub r9, r8		
	mov rax, r9

	ret
	
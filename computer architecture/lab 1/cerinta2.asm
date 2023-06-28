.data
	sir: .space 1000
	res: .space 4
	del: .asciz " "
	formatScanf: .asciz "%[^\n]%*c"
	formatPrintf: .asciz "%d\n"

.text

.global main

main:
	//scanf
	pushl $sir
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	//strtok
	pushl $del
	pushl $sir
	call strtok
	popl %ebx
	popl %ebx
	
	pushl %eax
	call atoi
	popl %ebx
	
	pushl %eax
	
et_for:
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	cmp $0, %eax
	je afisare

	movl %eax, res
	
	pushl %eax
	call atoi
	popl %ebx
	
	cmp $0, %eax
	je operatie
	
	pushl %eax
	
	jmp et_for
	
operatie:
	movl res, %edi
	xorl %ecx, %ecx
	movb (%edi, %ecx, 1), %bl

	cmp $97, %bl
	je et_add
	cmp $115, %bl
	je et_sub
	cmp $109, %bl
	je et_mul
	cmp $100, %bl
	je et_div

et_add:
	popl %eax
	popl %ebx
	addl %ebx, %eax
	pushl %eax
	
	jmp et_for

et_sub:
	popl %eax
	popl %ebx
	subl %eax, %ebx
	pushl %ebx
	
	jmp et_for

et_mul:
	popl %eax
	popl %ebx
	mull %ebx
	pushl %eax
	
	jmp et_for
	
et_div:
	xorl %edx, %edx
	popl %ebx
	popl %eax
	divl %ebx
	pushl %eax
	
	jmp et_for
	
afisare:
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
exit:
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80












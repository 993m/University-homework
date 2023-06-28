.data
	nr_lin: .space 4
	nr_col: .space 4
	nr_elem: .space 4
	index: .space 4
	res: .space 4
	nr: .space 4
	semn: .space 4
	il: .space 4
	ic: .space 4
	sir: .space 1700
	m1: .space 1700
	formatPrintf: .asciz "%d "
	formatScanf: .asciz "%[^\n]%*c"
	del: .asciz " "
	endl: .asciz "\n"
	
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
	
	//linii
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	pushl %eax
	call atoi
	popl %ebx
	
	movl %eax, nr_lin
	
	//coloane
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	pushl %eax
	call atoi
	popl %ebx
	
	movl %eax, nr_col

	//elemente matrice
	mull nr_lin
	movl %eax, nr_elem
	movl $0, index
et_for:
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	pushl %eax
	call atoi
	popl %ebx
	
	movl $m1, %edi
	movl index, %ecx
	movl %eax, (%edi, %ecx, 4)
	
	addl $1, %ecx
	cmp %ecx, nr_elem
	je continuare
	
	addl $1, index
	jmp et_for
	
continuare:
	//let
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx

	//rotire sau numar
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	pushl %eax
	call atoi
	popl %ebx
	
	cmp $0, %eax
	je rotire
	
	jmp numar
	
rotire:
	pushl nr_col
	pushl $formatPrintf
	call printf		
	popl %ebx
	popl %ebx
	
	pushl nr_lin
	pushl $formatPrintf
	call printf		
	popl %ebx
	popl %ebx

	movl $0, ic
for_col:
	movl ic, %eax
	cmp %eax, nr_col
	je exit
	
	movl nr_lin, %eax
	subl $1, %eax
	movl %eax, il
	
	for_lin:
		movl il, %eax
		cmp $0, %eax
		jl et
		
		movl $m1, %edi
		movl nr_col, %eax
		movl il, %ebx
		mull %ebx
		addl ic, %eax
		movl (%edi, %eax, 4), %eax
		
		pushl %eax
		pushl $formatPrintf
		call printf
		popl %ebx
		popl %ebx
		
		subl $1, il
		jmp for_lin

	et:
		incl ic
		jmp for_col	
			
numar:
	movl %eax, nr

	//operatie
	pushl $del
	pushl $0
	call strtok
	popl %ebx
	popl %ebx
	
	movl %eax, res

	movl res, %edi
	xorl %ecx, %ecx
	movb (%edi, %ecx, 1), %bl
	
	//print linii coloane
	pushl nr_lin
	pushl $formatPrintf
	call printf
	popl %ecx
	popl %ecx
	
	pushl nr_col
	pushl $formatPrintf
	call printf
	popl %ecx
	popl %ecx
	
	movl $0, index
	
	cmp $97, %bl
	je et_add
	cmp $115, %bl
	je et_sub
	cmp $109, %bl
	je et_mul
	cmp $100, %bl
	je et_div

et_add:
	movl $m1, %edi
	movl index, %ecx
	movl (%edi, %ecx, 4), %eax
	addl nr, %eax
	
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	incl index
	movl index, %ecx
	cmp %ecx, nr_elem
	je exit
	
	jmp et_add
	
et_sub:
	movl $m1, %edi
	movl index, %ecx
	movl (%edi, %ecx, 4), %eax
	subl nr, %eax
	
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	incl index
	movl index, %ecx
	cmp %ecx, nr_elem
	je exit
	
	jmp et_sub

et_mul:
	movl $m1, %edi
	movl index, %ecx
	movl (%edi, %ecx, 4), %eax
	mull nr
	
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	incl index
	movl index, %ecx
	cmp %ecx, nr_elem
	je exit
	
	jmp et_mul
	
et_div:
	//semn nr
	movl $1, semn
	
	movl nr, %ecx
	cmp $0, %ecx
	jl nr_neg
	
	jmp hai
	
nr_neg:
	movl semn, %eax
	movl $-1, %ecx
	mull %ecx
	movl %eax, semn
	
	movl nr, %eax
	movl $-1, %ecx
	mull %ecx
	movl %eax, nr
	
hai:	
	pushl semn
	movl $m1, %edi
	movl index, %ecx
	movl (%edi, %ecx, 4), %eax
	
	cmp $0, %eax
	jl el_neg
	
	jmp cont

el_neg:
	pushl %eax
	
	movl semn, %eax
	movl $-1, %ecx
	mull %ecx
	movl %eax, semn
	
	popl %eax
	
	movl $-1, %ecx
	mull %ecx
	
cont:
	//impartire
	xorl %edx, %edx
	divl nr
	
	//revenire la semn
	movl semn, %ecx
	mull %ecx
	  
	pushl %eax
	pushl $formatPrintf
	call printf
	popl %ebx
	popl %ebx
	
	incl index
	movl index, %ecx
	cmp %ecx, nr_elem
	je exit	
	
	popl semn
	jmp hai

exit:
	pushl $endl
	call printf
	popl %ebx	
	
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
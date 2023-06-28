.data
	sirhexa: .space 1000
	numar: .space 4
	cifra: .space 4 
	formatScanf: .asciz "%s"
	format_nr_poz: .asciz "%d "
	format_nr_neg: .asciz "-%d "
	format_variabila: .asciz "%c "
	format_operatie: .asciz "%s "
	let: .asciz "let"
	add: .asciz "add"
	sub: .asciz "sub"
	mul: .asciz "mul"
	div: .asciz "div"
	endl: .asciz "\n"
	
.text

.global main

main:
	// scanf
	pushl $sirhexa
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	movl $sirhexa, %edi
	xorl %ecx, %ecx
	
et_for:
	movb (%edi, %ecx, 1), %bl 
	cmp $0, %bl 
	je exit
	
	//instructiuni
	incl %ecx
	movb (%edi, %ecx, 1), %bl
	cmp $48, %bl
	je cif0_1	
	cmp $49, %bl
	je cif1_1
	cmp $50, %bl
	je cif2_1
	cmp $51, %bl
	je cif3_1
	cmp $52, %bl
	je cif4_1	
	cmp $53, %bl
	je cif5_1	
	cmp $54, %bl
	je cif6_1	
	cmp $55, %bl
	je cif7_1	
	cmp $56, %bl
	je cif8_1	
	cmp $57, %bl
	je cif9_1
	cmp $65, %bl
	je cif10_1
	cmp $66, %bl
	je cif11_1
	cmp $67, %bl
	je cif12_1	
	cmp $68, %bl
	je cif13_1
	cmp $69, %bl
	je cif14_1
	cmp $70, %bl
	je cif15_1
	
	
cont1:	
	movl $16, %eax
	mull cifra
	movl %eax, numar

	incl %ecx
	movb (%edi, %ecx, 1), %bl
	cmp $48, %bl
	je cif0_2
	cmp $49, %bl
	je cif1_2
	cmp $50, %bl
	je cif2_2
	cmp $51, %bl
	je cif3_2
	cmp $52, %bl
	je cif4_2	
	cmp $53, %bl
	je cif5_2	
	cmp $54, %bl
	je cif6_2	
	cmp $55, %bl
	je cif7_2	
	cmp $56, %bl
	je cif8_2	
	cmp $57, %bl
	je cif9_2
	cmp $65, %bl
	je cif10_2
	cmp $66, %bl
	je cif11_2
	cmp $67, %bl
	je cif12_2	
	cmp $68, %bl
	je cif13_2
	cmp $69, %bl
	je cif14_2
	cmp $70, %bl
	je cif15_2
	
cont2:
	movl cifra, %eax
	addl %eax, numar

	subl $2, %ecx
	movb (%edi, %ecx, 1), %bl
	cmp $56, %bl
	je nr_poz
	cmp $57, %bl
	je nr_neg
	cmp $65, %bl
	je variabila
	cmp $67, %bl
	je operatie
	
cont_for:
	addl $3, %ecx
	jmp et_for



nr_poz:
	pushl %ecx
	pushl numar
	pushl $format_nr_poz
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for
	
nr_neg:
	pushl %ecx
	pushl numar
	pushl $format_nr_neg
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

variabila:
	pushl %ecx
	pushl numar
	pushl $format_variabila
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

operatie:
	cmp $0, numar
	je et_let
	cmp $1, numar
	je et_add
	cmp $2, numar
	je et_sub
	cmp $3, numar
	je et_mul
	cmp $4, numar
	je et_div
	
et_let:

	pushl %ecx
	pushl $let
	pushl $format_operatie
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

et_add:
	pushl %ecx
	pushl $add
	pushl $format_operatie
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

et_sub:
	pushl %ecx
	pushl $sub
	pushl $format_operatie
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

et_mul:
	pushl %ecx
	pushl $mul
	pushl $format_operatie
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for

et_div:
	pushl %ecx
	pushl $div
	pushl $format_operatie
	call printf
	popl %eax
	popl %eax
	
	pushl $0
	call fflush
	popl %eax
	
	popl %ecx
	
	jmp cont_for


cif0_1:
	movl $0, %eax
	movl %eax, cifra
	jmp cont1
cif1_1:
	movl $1, %eax
	movl %eax, cifra
	jmp cont1
cif2_1:
	movl $2, %eax
	movl %eax, cifra
	jmp cont1
cif3_1:
	movl $3, %eax
	movl %eax, cifra
	jmp cont1
cif4_1:
	movl $4, %eax
	movl %eax, cifra
	jmp cont1
cif5_1:
	movl $5, %eax
	movl %eax, cifra
	jmp cont1
cif6_1:
	movl $6, %eax
	movl %eax, cifra
	jmp cont1
cif7_1:
	movl $7, %eax
	movl %eax, cifra
	jmp cont1
cif8_1:
	movl $8, %eax
	movl %eax, cifra
	jmp cont1
cif9_1:
	movl $9, %eax
	movl %eax, cifra
	jmp cont1
cif10_1:
	movl $10, %eax
	movl %eax, cifra
	jmp cont1
cif11_1:
	movl $11, %eax
	movl %eax, cifra
	jmp cont1
cif12_1:
	movl $12, %eax
	movl %eax, cifra
	jmp cont1
cif13_1:
	movl $13, %eax
	movl %eax, cifra
	jmp cont1
cif14_1:
	movl $14, %eax
	movl %eax, cifra
	jmp cont1
cif15_1:
	movl $15, %eax
	movl %eax, cifra
	jmp cont1




cif0_2:
	movl $0, %eax
	movl %eax, cifra
	jmp cont2
cif1_2:
	movl $1, %eax
	movl %eax, cifra
	jmp cont2
cif2_2:
	movl $2, %eax
	movl %eax, cifra
	jmp cont2
cif3_2:
	movl $3, %eax
	movl %eax, cifra
	jmp cont2
cif4_2:
	movl $4, %eax
	movl %eax, cifra
	jmp cont2
cif5_2:
	movl $5, %eax
	movl %eax, cifra
	jmp cont2
cif6_2:
	movl $6, %eax
	movl %eax, cifra
	jmp cont2
cif7_2:
	movl $7, %eax
	movl %eax, cifra
	jmp cont2
cif8_2:
	movl $8, %eax
	movl %eax, cifra
	jmp cont2
cif9_2:
	movl $9, %eax
	movl %eax, cifra
	jmp cont2
cif10_2:
	movl $10, %eax
	movl %eax, cifra
	jmp cont2
cif11_2:
	movl $11, %eax
	movl %eax, cifra
	jmp cont2
cif12_2:
	movl $12, %eax
	movl %eax, cifra
	jmp cont2
cif13_2:
	movl $13, %eax
	movl %eax, cifra
	jmp cont2
cif14_2:
	movl $14, %eax
	movl %eax, cifra
	jmp cont2
cif15_2:
	movl $15, %eax
	movl %eax, cifra
	jmp cont2
	
	
exit:
	pushl $endl
	call printf
	popl %ebx
	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80
	
	
	
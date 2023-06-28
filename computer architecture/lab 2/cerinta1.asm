.data
	n: .space 4
	m: .space 4
	v: .space 380
	f: .space 140
	x: .long 100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100
	l: .space 4
	elem: .space 4
	
	ghinion: .asciz "-1 "
	endl: .asciz "\n"
	formatScanf: .asciz "%d"
	formatPrintf: .asciz "%d "

.text

.global main

valid:
	//esp:ebp: (ebp v)(adresa intoarcere)
	pushl %ebp
	movl %esp, %ebp
	
	cmp $3, (%esi, %ebx, 4)
	jge fals
	
	//cmp $0, %ecx
	//je adevarat
	
	movl $x, %esi
	
	cmp $100, (%esi, %ebx, 4)
	je adevarat
	
	movl %ecx, %eax
	subl (%esi, %ebx, 4), %eax
	
	cmp m, %eax
	jg adevarat
	
fals:
	movl $f, %esi
	popl %ebp
	xorl %eax, %eax
	ret

adevarat:
	movl $f, %esi
	popl %ebp
	movl $1, %eax
	ret

bkt:
	//esp:ebp: (ebp v)(adresa intoarcere)
	pushl %ebp
	movl %esp, %ebp
	
	cmp %ecx, l
	je afisare_vector
	
	pushl %ebx
	
	movl (%edi, %ecx, 4), %ebx
	
	cmp $0, %ebx
	je nul
	
nenul:
	subl $1, (%esi, %ebx, 4)
	
	call valid
	//ebx, edi, esi restaurate, rezultat in eax
	
	cmp $0, %eax
	je cont_nenul
	
	addl $1, (%esi, %ebx, 4)
	
	movl $x, %eax
	pushl (%eax, %ebx, 4)
	
	movl %ecx, (%eax, %ebx, 4)
	incl %ecx
	
	call bkt
	//ebx se restaureaza
	
	subl $1, %ecx
	
	movl $x, %eax
	popl (%eax, %ebx, 4)
	
	subl $1, (%esi, %ebx, 4)	
	
cont_nenul:
	addl $1, (%esi, %ebx, 4)
	popl %ebx
	popl %ebp
	ret

nul:
	movl $1, %ebx
for_nul:
	cmp n, %ebx
	jg cont_nul
	
	call valid
	
	cmp $0, %eax
	je cont_for
	
	addl $1, (%esi, %ebx, 4)
	
	movl $x, %eax
	pushl (%eax, %ebx, 4)
	
	movl %ebx, (%edi, %ecx, 4)
	
	movl %ecx, (%eax, %ebx, 4)
	incl %ecx
	
	call bkt
	//ebx se restaureaza
	
	subl $1, %ecx
	
	movl $x, %eax
	popl (%eax, %ebx, 4)
	
	subl $1, (%esi, %ebx, 4)
	
cont_for:
	incl %ebx
	jmp for_nul
	
cont_nul:
	movl $0, (%edi, %ecx, 4)
	popl %ebx
	popl %ebp
	ret	

main:
	//citiri
	pushl $n
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	pushl $m
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	
	xorl %ecx, %ecx
	movl $v, %edi
	movl $3, %eax
	mull n
	movl %eax, l
	
	movl $f, %esi
citire_vector:
	cmp %ecx, l
	je apel
	
	pushl %ecx
	pushl $elem
	pushl $formatScanf
	call scanf
	popl %ebx
	popl %ebx
	popl %ecx
	
	movl elem, %ebx
	movl %ebx, (%edi, %ecx, 4)
	
	addl $1, (%esi, %ebx, 4)
	
	incl %ecx
	jmp citire_vector
	
afisare_vector:
	xorl %ecx, %ecx
	movl $v, %edi
	
	et_for:
		cmp %ecx, l
		je exit
	
		pushl %ecx
		pushl (%edi, %ecx, 4)
		pushl $formatPrintf
		call printf
		popl %ebx
		popl %ebx
		popl %ecx
		
		incl %ecx
		jmp et_for
	
apel:
	xorl %ecx, %ecx
	
	call bkt
	
	pushl $ghinion
	call printf
	popl %ebx

exit:
	pushl $endl
	call printf
	popl %ebx

	movl $1, %eax
	xorl %ebx, %ebx
	int $0x80

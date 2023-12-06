	.text
	.global _start
_start:
	movq $len, %rdx
	leaq msg(%rip), %rsi
	movq $1, %rdi
	movq $1, %rax
	syscall

	xorq %rdi, %rdi
	movq $60, %rax
	syscall

msg:	.ascii "Hi, ISEL!\n"
	len=.-msg


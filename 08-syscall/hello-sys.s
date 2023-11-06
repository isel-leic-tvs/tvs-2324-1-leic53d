	.text
	.global _start

_start:
	# write(1, msg, 14);
	movq $14, %rdx
	leaq msg(%rip), %rsi
	movq $1, %rdi

	movq $1, %rax
	syscall
	
	# exit(0);
	xorq %rdi, %rdi
	
	mov $60, %rax
	syscall
	
msg: 	.ascii "Hello, world!\n"	

	.end

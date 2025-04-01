/* gcc exit.S -nostdlib */
.global _start
_start:
    mov   $0, %rdi		# exit status
    mov  $60, %rax		# _exit
    syscall

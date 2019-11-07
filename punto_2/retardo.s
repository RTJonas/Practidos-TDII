.text
.arm
.global retardo
retardo:
LINK:	cmp r0,#0
	subne r0,r0,#1
	bne LINK
	mov pc,lr

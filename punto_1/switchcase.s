.text
.arm
.global switchcase
switchcase:
	cmp r0,#1
	addeq r0,r1,r2
	beq salida
	cmp r0,#2
	subeq r0,r1,r2
	beq salida
	cmp r0,#3
	subeq r0,r2,r1
	beq salida
	cmp r0,#4
	andeq r0,r2,r1
	movne r0,#0
salida:	mov pc,lr

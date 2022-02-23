  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\0"
	.text
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,1000
	jal	delay
	nop
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop


hexasc:
	li	$v0,0x30	# set $v0 to 0x30 which is '0' in ASCII-code		 
	
	andi	$a0,$a0,0xf	# 4 LSB in $a0 represent an ASCII-character, f=1111
		
	ble	$a0,0x09,true	# if input <= 9 go to true 
	nop
	addi	$v0,$v0,0x7	#add 0x7 to 0x31 so that we get the value for 'A' which is 0x41 in ASCII-code
	
true:
	add	$v0,$v0,$a0	# converts the value to ASCII-code
	jr	$ra		# jumps back to where the function was called
	nop
delay:
	PUSH($ra)
	
	addi 	$s0,$zero,0		# set i = 0
	move	$t0,$a0		# set $t0 = ms
	
while:
	bge	$s0,$t0,exit	# if ms <= 0 go to exit
	nop
	addi	$t0,$t0,-1	# ms--
	
forloop:	
	bge	$s0,60,forDone	# if i >= constant go to exit
	nop
	addi	$s0,$s0,1	# i + 1
	j	forloop
	nop
	
forDone:

	li	$s0,0		# set i = 0 again
	j	while		# jump to while
	nop	
	
exit:
	
	POP($ra)		# POP back the registers
	
	jr	$ra
	nop	
				
time2string:
	PUSH($ra)		# push $ra so that we can jump back to main and not hexasc after it has been used
	
	la	$t1,($a0)	# load address from $a0 to $s1
		
	andi	$t0,$a1,0xf000	# store 4 MSB from a1 to s0
	srl	$a0,$t0,12	# shift right 12 bits in $s0 so that these bits are LSB in $a0
	jal	hexasc		# jump and link to hexasc, convert the value to an ASCII-character
	nop
	sb	$v0,0($t1)	# store byte with offset 0 from $v0 to the MSB in $s1
	
	andi	$t0,$a1,0xf00	# store bits 11-8 from a1 to s0
	srl	$a0,$t0,8	# shift right 8 bits and store them as LSB in $a0
	jal	hexasc		# hexasc converts the bits to an ASCII-character
	nop
	sb	$v0,1($t1)	# store byte with offset 1
	
	li	$t2,0x3A	# load immediate 0x3A which is : in ASCII to $t1
	sb	$t2,2($t1)	# store byte with offset 2
	
	andi	$t0,$a1,0xf0	# store bits 7-4 from a1 to s0
	srl	$a0,$t0,4	# shift right 4 bits
	jal 	hexasc
	nop
	sb	$v0,3($t1)	# store byte with offset 3
	
	andi	$t0,$a1,0xf	# store bits 3-0 from a1 to s0	
	srl	$a0,$t0,0
	jal 	hexasc
	nop
	sb	$v0,4($t1)	# store byte with offset 4
	
	li	$t2,0x00	# load immediate $t1 with ASCII NULL
	sb	$t2,5($t1)	# store byte with offset 5
	
	
	POP($ra)		# POP back the PUSHED registers
	jr	$ra		# jump to return address
	nop

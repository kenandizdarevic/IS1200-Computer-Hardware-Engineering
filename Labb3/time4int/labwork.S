  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

.data
.global hexasc
.global delay
.global time2string
.global enable_interrupt
.text
enable_interrupt:
	ei
	jr $ra
	nop

hexasc:
	li	$v0,0x30	# set $v0 to 0x30 which is 0 in ASCII-code		 
	
	andi	$a0,$a0,0xf	# 4 LSB in $a0 represent an ASCII-character, f=1111
		
	ble	$a0,0x09,true	# if 0 <= 9 go to true 
	nop
	addi	$v0,$v0,0x7	#add 0x7 to 0x31 so that we get the value for 'A' which is 0x41 in ASCII-code
	
true:
	add	$v0,$v0,$a0	# converts the value to ASCII-code
	jr	$ra		# jumps back to where the function was called
	nop
delay:
	PUSH $ra
	
	addi 	$s0,$zero,0	# set i = 0
	move	$t0,$a0		# set $t0 = ms
	addi	$t1,$0,3850	# for loop constant
	
while:
	bge	$s0,$t0,exit	# if ms <= 0 go to exit
	nop
	addi	$t0,$t0,-1	# ms--
	
forloop:	
	bge	$s0,$t1,forDone	# if i >= constant go to exit
	nop
	addi	$s0,$s0,1	# i + 1
	j	forloop
	nop
	
forDone:

	li	$s0,0		# set i = 0 again
	j	while		# jump to while
	nop	
	
exit:
	
	POP $ra		# POP back the registers
	
	jr	$ra
	nop	
				
time2string:
	PUSH $ra		# push $ra so that we can jump back to main and not hexasc after it has been used
	
	la	$s1,($a0)	# load address from $a0 to $s1
		
	andi	$s0,$a1,0xf000	# store 4 MSB from a1 to s0
	srl	$a0,$s0,12	# shift right 12 bits in $s0 so that these bits are LSB in $a0
	jal	hexasc		# jump and link to hexasc, convert the value to an ASCII-character
	nop
	sb	$v0,0($s1)	# store byte with offset 0 from $v0 to the MSB in $s1
	
	andi	$s0,$a1,0xf00	# store bits 11-8 from a1 to s0
	srl	$a0,$s0,8	# shift right 8 bits and store them as LSB in $a0
	jal	hexasc		# hexasc converts the bits to an ASCII-character
	nop
	sb	$v0,1($s1)	# store byte with offset 1
	
	li	$t1,0x3A	# load immediate 0x3A which is : in ASCII to $t1
	sb	$t1,2($s1)	# store byte with offset 2
	
	andi	$s0,$a1,0xf0	# store bits 7-4 from a1 to s0
	srl	$a0,$s0,4	# shift right 4 bits
	jal 	hexasc
	nop
	sb	$v0,3($s1)	# store byte with offset 3
	
	andi	$s0,$a1,0xf	# store bits 3-0 from a1 to s0	
	srl	$a0,$s0,0
	jal 	hexasc
	nop
	sb	$v0,4($s1)	# store byte with offset 4
	
	#suprise
	andi	$s0,$s0,0x001
	beq	$s0,1,odd
	
	li	$a0,14
	jal 	hexasc
	nop
	sb	$v0,5($s1)
	jal	end
	nop

odd:
	li	$a0,13
	jal	hexasc
	nop
	
	sb	$v0,5($s1)
	jal	end	
	nop	

end:		
	li	$t1,0x00	# load immediate $t1 with ASCII NULL
	sb	$t1,6($s1)	# store byte with offset 5
	
	
	POP $ra		# POP back the PUSHED registers
	jr	$ra		# jump to return address
	nop
	
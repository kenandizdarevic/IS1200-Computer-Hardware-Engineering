  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:	
	li	$a0,17		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  
hexasc:
	li	$v0,0x30	# set $v0 to 0x30 which is 0 in ASCII-code		 
	
	andi	$a0,$a0,0xf	# 4 LSB in $a0 represent an ASCII-character, f=1111
		
	ble	$a0,0x9,true	# if 0 <= 9 go to true 
	nop
	#else
	addi	$v0,$v0,0x7	#add 0x7 to 0x31 so that we get the value for 'A' which is 0x41 in ASCII-code
	
true:
	add	$v0,$v0,$a0	# converts the value to ASCII-code
	jr	$ra		# jumps back to where the function was called
	nop

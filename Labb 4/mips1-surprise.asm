.text

	addi 	$a0, $zero, 4 	# the immediate is our constant
	add	$v0, $v0, $a0	# set sum to answer
	
	# we use $a0 as our i for the loop
loop:
	beq	$a0, $zero, done	# checks if n == 0
	addi	$a0, $a0, -1		# i--
	add	$a1, $zero, $a0		# set $a1 = $a0
	beq	$a0, $zero, done	# if i == 0 go to done
	mul	$v0, $v0, $a1		# $v0 * $a1
	beq	$zero, $zero, loop	# continue iterating in the  loop
	

done:
	beq	$zero, $zero, done
	
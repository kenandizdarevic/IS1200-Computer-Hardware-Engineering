.text

	addi 	$a0, $zero, 3	# the immediate is n
	add	$v0, $v0, $a0	# set answer = n
	addi	$a1, $a0, -2	# i == (n - 2)
	addi	$at, $zero, 1	# at == 1
	
	beq	$a0, $zero, zero	# if(n == 0) go to zero
	beq	$a0, $at, done		# if(n == 1) go to done
	
loop:
	beq	$a1, $zero, done		# if(i == 0) go to done	
	addi 	$a1, $a1, -1		# i--
	addi 	$a2, $a0, -2		# j == (n - 2)
	addi	$a0, $a0, -1		# n--
	add 	$a3, $v0, $zero		# sum = answer
	
multiply:
	beq	$a2, $zero, loop	# if(j == 0) go to the outer loop
	add	$v0, $v0, $a3		# answer += sum
	addi	$a2, $a2, -1		
	
	beq	$zero, $zero, multiply	# continue iterating in the nested loop
done:
	beq	$zero, $zero, done	# loop forever in done
				
zero:
	addi 	$v0, $zero, 1		# 0! = 1
	beq	$zero, $zero, done	# go to done
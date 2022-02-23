# Written by Kenan Dizdarevic & Abud David Zoughbi

.text

	addi	$v1, $zero, 3	# this value is n
	addi	$a1, $zero, 1	# i = 1
	addi	$a2, $zero. 1	# j = 1

loop:
	beq 	$a1, $v1, done	# if n = i go to done
	
	
multiply:
	beq	$a1, $v1, result
	

result:
	
	
	addi	$a1, $zero, 1	# i++

done:
	beq	$zero, $zero, done
	
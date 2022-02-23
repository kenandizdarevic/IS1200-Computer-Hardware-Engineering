
.text

	addi $a0,$0,4     # set $a0 to 4
	addi $v0,$a0,2	  # test addi, set $v0 = 6
	add  $v0,$v0,$a0  # start of counter. Should be 10 $v0 = 10
loop:	beq  $v0,$a0,done # test, jump to done. 10 = 4 1st iteration
        addi $v0,$v0,-3   # decrement. Loops twice.10 - 3 = 7, 7 - 3 = 4
        beq  $0,$0,loop   # emulating an unconditional jump
done:	add  $0,$0,$0	  # NOP	
	

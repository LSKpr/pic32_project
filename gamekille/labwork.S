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
  #
  # Please add your own code below this line
  #
.data
    .align 2
mytime:    .word 0x5957
timstr:    .ascii "text more text lots of text\0"



.text
.global enable_interrupt
enable_interrupt:
	ei
	jr $ra
	nop
hexasc:
     
      andi $a0,$a0,0xf    # only 4 least significant bits are needed, ignore other bits
      li $v0,0x30         # $v0 = 0x30 ('0' in ascii)
      add $v0,$v0,$a0     # add $a0 to $v0
      blt $a0,0xa,end     # if $a0 < 0xa (10 in decimal), jump to end
      nop
      addi $v0,$v0,7      # add 7 to $v0 to get the ascii code for 'A'
end:
      jr $ra
      nop


.global delay
delay:  

    PUSH $ra
    PUSH $s0
    PUSH $s1

    whileLoop:
    blez $a0, stop
    nop
    sub $a0, $a0, 1

    li $s0, 2200000
    move $s1, $0

    forLoop:
    beq $s0, $s1, whileLoop
    nop
    addi $s1, $s1, 1
    j forLoop
    nop

    stop:
    POP $s1
    POP $s0
    POP $ra

    jr $ra
    nop

.global time2string
time2string:	# a0 = addr,	a1 = time(0x0000MMSS)
	#	X0:00
	PUSH $s0
	PUSH $s1
	PUSH $ra
	move	$s0,$a0		#	addr in s0
	move	$s1,$a1		#	s1 <= a1 
	and	$a0,$s1,0xF000	# using a0 as temporary reg
	srl	$a0,$a0,12
	jal	hexasc
	nop
	sb	$v0, 0($s0)
	
	
	#0X:00
	and	$a0,$s1,0x0F00	# using a0 as temporary reg
	srl	$a0,$a0,8
	jal	hexasc
	nop
	sb	$v0, 1($s0)
	
	li $a0,0x3A	#	':'
	sb $a0,2($s0)
	
	#00:X0
	and	$a0,$s1,0x00F0
	srl	$a0,$a0,4
	jal	hexasc
	nop
	sb	$v0, 3($s0)
	
	#00:0X
	and	$a0,$s1,0x000F
	jal	hexasc
	nop
	sb	$v0, 4($s0)
	
	and $a0, $s1, 0x00FF

	bne $a0, 0x000,else1 #if a0 == 0 
	nop
	li $a0,0x58
	sb $a0,5($s0)
	li $a0, 0x00
	sb $a0,6($s0)
	j XXX
	nop
	else1:
	li $a0, 0x00	# nullbyte
	sb $a0,5($s0)
	XXX:
	
	POP $ra
	POP $s1
	POP $s0
		
	jr $ra
	nop

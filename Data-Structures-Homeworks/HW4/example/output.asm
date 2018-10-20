li 	$t0, 4 	#variable a	
li 	$t1, 3 	#variable b
li 	$t2,12	#variable c

li 	$t3,3	#to keep 3
mult 	$t1,$t3	#b*3
mflo	$t3	#t3 keeps result of b*3
	
sub 	$t4,$t0,$t3	#t4=t3-a
move 	$t1,$t4		#t1=t4

li	$t3,3		#t3=3
div 	$t0,$t3		
mflo 	$t3		#keeps divison result of t0/t3
	
li 	$t4,21
mult 	$t3,$t4
mflo 	$t2
add 	$t3,$t2,$t1
move 	$t2,$t3

move 	$a0, $t2 	# print m.
li 	$v0, 1 		#print_in
syscall			#system call

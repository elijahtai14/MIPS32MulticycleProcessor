# we want C = AB. $t0 is the base address of A, and $t1 is the base address of B, and $t2 is the base address of C
# PSUEDOCODE:
#	row_A = 0
#	row_B = 0
#	cell_C = 0
#	for row_A in range (0, 8):
#		for col_B in range (0, 8):
#			sum = 0
#			for counter in range (0, 8):
#				sum += A[row_A][counter] * B[counter ][col_B]
#			C[cell_C] = sum
#			cell_C += 1

main: 			add 	$s0, $0, $0			# s0 = 0, where s0 is [0, 7]  the current row of A
				add 	$s1, $0, $0			# s1 = 0, where s1 is [0, 7]  the current column of B
				add 	$s2, $0, $0			# s2 = 0, where s2 is [0, 63] the current cell of C
				add 	$s3, $0, $0 		# s3 = 0, where s3 is a counter that will help us with the summation
				addi	$s4, $0, 8			# s4 = 8, where s4 is n, and A, B, C are n x n matrices

for_each_row_A: beq 	$s0, $s4, end		# loop through each row of A
				add 	$s1, $0, $0			# (reset inner loop) 

for_each_col_B: beq 	$s1, $s4, cont  	# loop through each column of B
				add 	$s3, $0, $0			# (reset inner loop)
				add 	$s5, $0, $0			# s5 = 0, where s5 is the sum that will become a cell in C

perform_sum: 	beq		$s3, $s4, cont2		# loop through cells
				mul	$t3, $s0, $s4		# compute address for A[row][cell] = A[s0][s3] 
				add	$t3, $t3, $s3
				sll	$t3, $t3, 2
				add	$t3, $t3, $t0		
				lw		$t5, 0($t3)			# load A[row][cell] into $t5
	
				mul		$t4, $s3, $s4		# compute address for B[cell][col] = B[s3][s1] 
				add	$t4, $t4, $s1
				sll		$t4, $t4, 2
				add	$t4, $t4, $t1		
				lw		$t6, 0($t4)			# load B[cell][col] into $t6

				mul		$t7, $t5, $t6		# t7 = A[row][cell] * B[cell][col]
				add 	$s5, $s5, $t7		# sum += A[row][cell] * B[cell][col]

				addi	$s3, $s3, 1			# increment and loop
				j perform_sum

cont2: 			sll		$t3, $s2, 2			# compute address for C[cell_C] = C[s2]
				add 	$t3, $t3, $t2		  
				sw $s5, 0($t3)				# C[cell_C] = sum

				addi $s2, $s2, 1			# cell_C += 1

				addi	$s1, $s1, 1			# increment and loop
				j for_each_col_B

cont: 			addi	$s0, $s0, 1			# increment and loop
				j for_each_row_A
end: 			nop







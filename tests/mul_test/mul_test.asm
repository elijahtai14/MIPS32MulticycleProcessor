main:	addi $2, $0, 5		# Set $2 = 5
		addi $3, $0, 7		# Set $3 = 7
		mul $4, $2, $3		# Set $4 = 5 x 7 = 35
		addi $5, $0, 5		# Set $5 = 5
		mul $5, $0, $2		# Set $5 = 5 x 0 (checking if multiplication by zero works)
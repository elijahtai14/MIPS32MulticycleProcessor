import random
import numpy as np

N = 16
b = []
c = []

# Creating two NxN random matrices
for _ in range (N):
	temp = []
	temp2 = []
	for __  in range (N):
		temp.append(random.randint(1, 101))
		temp2.append(random.randint(1, 101))
	b.append(temp)
	c.append(temp2)

BMAT = np.array(b)
CMAT = np.array(c)


def strassen (BM, CM):
	n = len(BM)
	if n == 2:
		return np.matmul(BM, CM)
	else:
		n = int(n / 2)
		A = BM[:n, :n]
		B = BM[:n, n:]
		C = BM[n:, :n]
		D = BM[n:, n:]
		E = CM[:n, :n]
		F = CM[:n, n:]
		G = CM[n:, :n]
		H = CM[n:, n:]

		print (A)
		print (B)

		p1 = strassen(A,F-H)
		p2 = strassen(A+B,H)
		p3 = strassen(C+D,E)
		p4 = strassen(D,G-E)
		p5 = strassen(A+D,E+H)
		p6 = strassen(B-D,G+H)
		p7 = strassen(A-C,E+F)

		Q1 = p5 + p4 - p2 + p6
		Q2 = p1 + p2
		Q3 = p3 + p4
		Q4 = p1 + p5 -p3 - p7

		return np.concatenate((np.concatenate((Q1, Q3)), np.concatenate((Q2, Q4))), axis = 1)

print (np.matmul(BMAT, CMAT))
print (strassen(BMAT, CMAT))


		






	



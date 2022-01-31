import random

A = [];

for i in range(0,1000,1):
	n = random.randint(0, 100000)
	if (i == 0):
		A.append(n);
	else:
		flag = 1
		while (flag != 0):
			flag = 0
			for j in range(0, len(A), 1):
				if (A[j] == n):
					flag = 1
					break
			if (flag == 1):
				n = random.randint(0, 100000)
				continue
			A.append(n)
			flag = 0

for i in range(0, len(A), 1):
	print(A[i])
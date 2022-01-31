import random

A = ["BMW", "Audi", "Mersedes", "Ford", "Honda", "Hyundai", "Kia", "Lada", "Mazda", "Skoda", "Toyota","Lexus","Suzuki","Chevrolet", "Jeep"]
B = ["Belgium", "USA", "Russia", "Germany", "Greece", "Belarus","Italy","England","Latvia","Spain","Monaco","Ulraine","Finland","France","Estonia","Sweden","Montenegro","Portugal"]
C = ["new", "old"]
D = ["black", "red", "white", "blue","yellow", "green", "purple"]

ran = 40
print(ran)

for i in range (0,ran):
	name = random.randint(0, len(A) - 1)
	country = random.randint(0, len(B) - 1)
	price = random.randint(500000,3000000)
	color = random.randint(0, len(D) - 1)
	condition = random.randint(0,1)
	if condition == 0:
		garanty = random.randint(1,10)
		print(A[name], B[country], price,D[color], C[condition], garanty)
	if condition == 1:
		year = random.randint(1980,2020)
		millage = random.randint(10000,200000)
		repairs = random.randint(0,5)
		owners = random.randint(1,5)
		print(A[name], B[country], price, D[color], C[condition], year,millage,repairs,owners)
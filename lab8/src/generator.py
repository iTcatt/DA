import random

n = random.randint(3, 10)

m = random.randint(1, 20)

strs = []
for i in range(n):
    l = random.randint(-5, 5)
    r = random.randint(l, 15)
    s = str(l) + " " + str(r)
    strs.append(s)


with open("test.txt", "w", encoding="utf-8") as file:
    file.write(str(n) + "\n")
    file.write("\n".join(strs))   
    file.write("\n" + str(m) + "\n")
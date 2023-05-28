import random

pattern = []
text = []

m = 100
n = 1000000

for i in range(m):
    pattern.append(str(random.randint(0, 100)))

lol = [elem for elem in pattern]
for i in range(0, n, m):

    if i % 39 == 0:
        for elem in pattern:
            text.append(elem)    
    else:
        random.shuffle(lol)
        for elem in lol:
            text.append(elem)

with open("test.txt", "w", encoding="utf-8") as file:
    file.write(" ".join(pattern))
    file.write("\n")
    file.write("\n".join(text))



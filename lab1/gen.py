import random

def gen():
    key = random.randint(0, 10000)
    alphabet = "abcdefghigklmnopqrstuvwxyz1234567890"
    s = ""
    for i in range(random.randint(1, 20)):
        s += random.choice(alphabet)
    result = str(key) + "\t" + s + "\n"
    return result

n = 100
# n = 1
with open("lol.txt", "w", encoding="utf-8") as input:
    for i in range(n):
        input.write(gen())

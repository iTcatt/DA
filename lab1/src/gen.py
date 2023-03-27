import random

def gen():
    key = random.randint(0, 2**64-1)
    alphabet = "abcdefghigklmnopqrstuvwxyz1234567890"
    s = ""
    for i in range(random.randint(1, 2048)):
        s += random.choice(alphabet)
    result = str(key) + "\t" + s + "\n"
    return result

n = 1000
# n = 1
with open("input.txt", "w", encoding="utf-8") as input:
    for i in range(n):
        input.write(gen())

import random
import string
from contextlib import redirect_stdout

def randomword(length):
    letters = string.ascii_uppercase + string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(length))

A = []
N = 500000
with open('input.txt', 'w') as f:
    with redirect_stdout(f):
        for i in range(N):
            key = randomword(random.randint(1, 200))
            value = random.randint(1, 100000000)
            print("+ %s %d" % (key, value))
            A.append([key, value])
        print("#")
        random.shuffle(A)
        for i in A:
            print("%s" % (i[0]))
        print("#")
        for i in A:
            print("- %s" % (i[0]))
        print("#")
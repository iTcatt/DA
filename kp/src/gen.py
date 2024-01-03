import random
import string

def generate_compress_test(n):
    text = ''.join(random.choice(string.ascii_lowercase) for _ in range(n))
    return f"compress\n{text}\n"

def generate_decompress_test(n):
    codes = []
    for _ in range(n):
        elem = (str(random.randint(1, 100)), str(random.randint(0, 26)))
        codes.append(' '.join(elem))
    return codes
    
n = int(input())

with open("test.txt", "w", encoding="utf-8") as file:
    file.write(generate_compress_test(n))
    res = generate_decompress_test(n)
    file.write('decompress\n')
    file.write('\n'.join(res))


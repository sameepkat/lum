import random
import string

source = '''
message = "Hello, World!"
printer = print
printer(message)
'''

def random_identifier(length=8):
    chars = string.ascii_letters
    return "_" + "".join(random.choice(chars) for _ in range(length))

identifier_map = {
    "message": random_identifier(),
    "printer": random_identifier(),
}

randomized = source
for old, new in identifier_map.items():
    randomized = randomized.replace(old, new)

print("Randomized code:")
print(randomized)

print("Output:")
exec(randomized)
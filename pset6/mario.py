from cs50 import get_int

# get pyramids height from user
while True:
    height = get_int("Height: ")
    # height must be integer between 1 and 8, inclusive.
    if height > 0 and height < 9:
        break

for i in range(1, height + 1):
    for j in range(1, height + 1):
        if j > (height - i):
            # print brick
            print("#", end="")
        else:
            # print the blank space before bricks
            print(" ", end="")
        if j == height:
            # print the gap
            print("  ", end="")
            # print the second part of pyramid
            print("#" * i, end="")
    print("")

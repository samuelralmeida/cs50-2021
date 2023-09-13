import cs50
import sys
import csv


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py DATABASE_FILENAME SEQUENCE_FILENAME")
        return

    # Open sequence data
    with open(sys.argv[2], "r") as file:
        sequence = file.readline()

    result = "No match"
    # Open database
    with open(sys.argv[1], "r") as file:
        reader = csv.reader(file)
        headers = next(reader)

        # Count consecutive repeats of the STR
        STRS = dict()
        for key in headers[1:]:
            STRS[key] = countSTR(sequence, key)

        # Compare sequence with individuals
        for person in reader:

            match = True
            for i in range(1, len(headers)):
                if int(person[i]) != STRS[headers[i]]:
                    match = False
                    break

            if match == True:
                result = person[0]
                break

    print(result)


def countSTR(sequence, str_target):

    current_count = 0
    max_count = 0
    target_len = len(str_target)

    while True:

        # Find target in sequence
        index = sequence.find(str_target)

        # Target has not found
        if index < 0:
            break

        # Target in firts position
        elif index == 0:
            current_count += 1

        # Target not in first position
        else:
            # First target has been found
            if current_count == 0:
                current_count += 1

            # Target has been found, but not in sequence, so start the counter again
            else:
                if current_count > max_count:
                    max_count = current_count
                current_count = 1

        # Cut sequence right after target has been found
        sequence = sequence[(index + target_len):]

    if current_count > max_count:
        max_count = current_count

    return max_count


if __name__ == "__main__":
    main()

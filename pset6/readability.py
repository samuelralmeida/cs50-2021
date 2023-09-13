from cs50 import get_string


def main():
    # Get input text
    text = get_string("Text: ")

    # counters
    letters = 0
    words = 0
    sentences = 0

    for i in range(len(text)):
        # count only if char is a letter
        if text[i].isalpha():
            letters += 1

        # count blank space
        elif text[i] == " ":
            words += 1

        # count sentences mark (! . ?)
        elif text[i] == "!" or text[i] == "." or text[i] == "?":
            sentences += 1

    # sum last word
    words += 1

    # average number of letters per 100 words
    l = (letters / words) * 100

    # average number of sentences per 100 words
    s = (sentences / words) * 100

    grade = int(round(0.0588 * l - 0.296 * s - 15.8))

    # check grade
    if grade < 0:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade ", grade)


if __name__ == "__main__":
    main()

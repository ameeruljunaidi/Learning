from cs50.cs50 import get_string


def main():
    # Get text and comput score
    text: str = get_string("Text: ")
    score: int = compute_score(text)

    # Print out put based on score
    print(output(score))


def compute_score(text: str) -> int:
    # Count letters, spaces, and punctuations
    letter_count: int = 0
    word_count: int = 1
    sentence_count: int = 0

    for i in text:
        if i.isalpha():
            letter_count += 1
        if i.isspace():
            word_count += 1
        if i in [".", "!", "?"]:
            sentence_count += 1

    # Calculate L & S
    L: float = float(letter_count / word_count * 100)
    S: float = float(sentence_count / word_count * 100)

    # Calculate the score
    score: float = 0.0588 * L - 0.296 * S - 15.8

    return round(score)


def output(score: int) -> str:
    if score < 1:
        return "Before Grade 1"
    if score > 16:
        return "Grade 16+"
    else:
        return f"Grade {score}"


if __name__ == "__main__":
    main()

from cs50.cs50 import get_int


def main():
    n: int = get_positive_int()
    pyramid(n)


def get_positive_int() -> int:
    while True:
        n: int = get_int("Heigh: ")
        if n > 0 and n < 9:
            break
    return n


def pyramid(size: int) -> None:
    for i in range(1, size + 1):
        print(" " * (size - i), end="")
        print("#" * i, end="")
        print("  ", end="")
        print("#" * i, end="\n")


if __name__ == "__main__":
    main()

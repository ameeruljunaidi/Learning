import sys
from typing import Any
import csv


def main():

    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")

    # Store filenames
    data_filename: str = sys.argv[1]
    sequence_filename: str = sys.argv[2]

    # Get list of strs
    str_list: list[str] = get_str_list(data_filename)

    # Get persons data
    persons_data: list[dict[str, Any]] = get_persons_data(data_filename, str_list)

    # Go through sequence file and return name of match
    match: str = get_match(sequence_filename, persons_data, str_list)

    # Print the result from get_match
    print(match)


def get_persons_data(filename: str, str_list: list[str]) -> list[dict[str, Any]]:
    """Return a dictionary with person's data.

    Structure:
    {
        "name": str,
        "str_data": dict[str, int]
    }

    Args:
        filename (str): Filename that contains all the persons.

    Returns:
        dict[str, Any]: Returns a dictionary.
    """

    # Get return list
    return_list: list[dict[str, Any]] = []
    with open(filename, "r") as file:
        # Create a reader variable
        reader = csv.DictReader(file)

        # Iterate through row
        for row in reader:
            # Create a temp dict to store data
            temp_dict: dict[str, Any] = {}

            # Add name to temp dict
            temp_dict["name"] = row["name"]

            # Create a temp dict and list for strs
            str_count_dict: dict[str, int] = {}
            for item in str_list:
                str_count_dict[item] = int(row[item])

            # Add list of strs to temp dict
            temp_dict["str_data"] = str_count_dict

            # Add temp dict to list
            return_list.append(temp_dict)

    return return_list


def get_str_list(filename: str) -> list[str]:
    """Return list of strs

    Args:
        filename (str): Filename that contains information about persons.

    Returns:
        list[str]: List of avaialable strs.
    """

    # Create an empty list
    str_list: list[str] = []

    # Open file and get the strs
    with open(filename, "r") as file:
        reader = csv.reader(file)
        for row in reader:
            for column in range(1, len(row)):
                str_list.append(row[column])
            break

    return str_list


def get_match(filename: str, persons: list[dict[str, Any]], str_list: list[str]) -> str:
    """Return a name if there is a match, if not return "No Match"

    Args:
        filename (str): Filename of the sequence file
        persons (list[dict[str, Any]]): The persons list
        str_list (list[str]): List of all the strs available
    """
    # Initialize the count of all the strs first
    str_count: dict[str, int] = {}
    for item in str_list:
        str_count[item] = 0

    # Open the file and add the sequence to memory
    with open(filename, "r") as file:
        sequence: str = file.read()

    # Go through each strs and see if it shows up
    # Get the length of sequence and store in variable
    seql: int = len(sequence)

    # Loop through every item in list of str (look for these strings)
    for item in str_list:
        # Get length of item
        iteml: int = len(item)
        temp_count: int = 0

        # Go through all the chars in sequence
        for i in range(seql):
            # Max index is set based on the length of the str in current loop
            # This is used for slicing (chunking)
            max_index: int = i + iteml

            # If not end of sequence
            if max_index < seql:
                # Get the text chunk
                text_chunk: str = sequence[i:max_index]
                previous_text_chunk: str = sequence[i - iteml : max_index - iteml]
                next_text_chunk: str = sequence[i + iteml : max_index + iteml]

                # Check to make sure we don't do even less than first character
                if max_index + iteml < seql:

                    # If text chunk == str in current loop  count is not empty
                    if text_chunk == item and temp_count != 0:

                        # If current text chunk == previous chunk, it's consecutive, add
                        # Need to fix this, something is wrong the problem is when it's a singular TPR
                        if (
                            text_chunk == previous_text_chunk
                            and text_chunk == next_text_chunk
                            and temp_count > 0
                        ):
                            temp_count += 1
                        elif (
                            text_chunk == previous_text_chunk
                            and text_chunk != next_text_chunk
                            and temp_count > 0
                        ):
                            temp_count += 1
                            if temp_count > str_count[item]:
                                str_count[item] = temp_count
                            temp_count = 0

                    # If count is empty, just add, no more checking necessary
                    elif (
                        text_chunk == item
                        and text_chunk != previous_text_chunk
                        and temp_count == 0
                    ):
                        temp_count += 1

        if temp_count > str_count[item]:
            str_count[item] = temp_count
        temp_count = 0

    # Loop through persons list
    match: str = get_name(persons, str_list, str_count)

    return match


def get_name(
    persons: list[dict[str, Any]], str_list: list[str], str_count: dict[str, int]
) -> str:
    """Return a name if there is a match, if not, return "No Match"

    Args:
        persons (list[dict[str, Any]]): A list of all the persons' dict
        str_list (list[str]): A list of all the available strs
        str_count (dict[str, int]): Current count of consequtive strs

    Returns:
        str: Returns either a name or "No Match"
    """

    # Get list of names first and store in list
    names: dict[str, int] = {}
    for person in persons:
        names[person["name"]] = 0

    # Loop through every person in memeory
    for person in persons:
        # Create a checker
        checker: int = 0

        # Loop through every str available
        for item in str_list:
            # If count is the same, add 1 to checker
            if person["str_data"][item] == str_count[item]:
                checker += 1
            # If even one item is not the same, set it back to zero
            else:
                checker = 0

        # If checker is good, return person's name
        if checker == len(str_list):
            return person["name"]

    return "No Match"


if __name__ == "__main__":
    main()

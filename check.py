import itertools

# Function to find valid solutions for a given input number
def find_valid_solutions(input_number, dictionary_file):
    # Load the dictionary file into a set for efficient lookup
    with open(dictionary_file, 'r') as dictionary_file:
        dictionary = set(word.strip().upper() for word in dictionary_file)

    # Generate all permutations of the English alphabet for the unique digits in the input
    unique_digits = ''.join(set(input_number))
    letter_permutations = itertools.permutations('ABCDEFGHIJKLMNOPQRSTUVWXYZ', len(unique_digits))

    # Function to construct words and check if they are in the dictionary
    def is_valid_word(word):
        return word in dictionary

    # Iterate through letter permutations and construct words
    valid_solutions = []
    for permutation in letter_permutations:
        digit_to_letter = dict(zip(unique_digits, permutation))
        word = ''.join(digit_to_letter[digit] for digit in input_number)
    
        if is_valid_word(word) and is_valid_word( word[::-1]):
            valid_solutions.append(word)

    return valid_solutions

# Input number and dictionary file
input_number = input("Enter a number: ")
dictionary_file = "dictionary"

# Find valid solutions for the input number
valid_solutions = find_valid_solutions(input_number, dictionary_file)

# Print the count of valid solutions and the solutions themselves
print("Found", len(valid_solutions), "solutions for input", input_number + ":")
for solution in valid_solutions:
    print(solution)

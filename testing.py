import itertools

# Load the dictionary file into a set for efficient lookup
with open('dictionary', 'r') as dictionary_file:
    dictionary = set(word.strip().upper() for word in dictionary_file)

# Input numbers and their corresponding letters
input_numbers = ["9567", "1085", "10652"]
input_letters = {
    '9': 'D',
    '5': 'E',
    '1': 'M',
    '6': 'N',
    '0': 'O',
    '8': 'R',
    '7': 'S',
    '2': 'Y'
}

# Function to check if a word is valid
def is_valid_word(word):
    return word in dictionary

# Function to generate all possible letter assignments for a number
def generate_letter_assignments(number):
    return [''.join(letters) for letters in itertools.permutations([input_letters[digit] for digit in number])]

# Iterate through all possible letter assignments for each number
valid_solutions = []

for number in input_numbers:
    letter_assignments = generate_letter_assignments(number)
    
    # Construct words and check if they are in the dictionary
    for assignment in letter_assignments:
        word = ''
        for digit in number:
            word += assignment[number.index(digit)]
        
        if is_valid_word(word):
            valid_solutions.append(word)

# Print the count of valid solutions and the solutions themselves
print("Found", len(valid_solutions), "solutions:")
for solution in valid_solutions:
    print(solution)

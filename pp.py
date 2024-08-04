# Define the path to your dictionary file
dictionary_file = "dictionary"

# Create an empty set to store valid words from the dictionary
valid_words = set()

# Read valid words from the dictionary file and store them in the set
with open(dictionary_file, 'r') as file:
    for line in file:
        if len(line) == 2:
          valid_words.add(line.strip().upper())  # Assuming dictionary words are in uppercase

# Initialize a fail_count variable to keep track of combinations that don't exist
fail_count = 0

# Iterate through all combinations of two distinct letters
for letter1 in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
    for letter2 in 'ABCDEFGHIJKLMNOPQRSTUVWXYZ':
        if letter1 != letter2:
            combination = letter1 + letter2
            found = False
            # Iterate through words in valid_words
            for word in valid_words:
                if word[:2] == combination:
                    found = True
                    break  # Exit the inner loop once a valid combination is found
            # If the combination was not found in any word, increment the fail_count
            if not found:
                print(combination)
                fail_count += 1

# Print the fail_count
print("Fail Count:", fail_count)



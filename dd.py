# Initialize a counter for words matching the criteria
count = 0
def has_duplicates(word):
    seen = set()
    for letter in word:
        if letter in seen:
            return True
        seen.add(letter)
    return False
# make a function that will take a list of words as parameter (char***) and guessed word as parameter of char type, third parameter is position.

# inside function intialize count = 0,


wordslist=[]
# Open the file for reading
with open(r'D:\C++\dictionary', 'r') as file:
    # Loop through each line in the file
    for line in file:
        # Split the line into words
        words = line.split()
        # Iterate through the words
        for word in words:
            if not has_duplicates(word) :
            # Check if the word is 6 characters long and doesn't contain 'a'
                if len(word) == 5:
                    # Print the word
                    print(word)
                    wordslist.append(word)
                    #print(word)
                    # Increment the counter
                    count += 1

#ae
print("Count of words with length 5:",len(wordslist))

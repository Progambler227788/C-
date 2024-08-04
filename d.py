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
                if len(word) == 6 and 'a' not in word.lower():
                    # Print the word
                    wordslist.append(word)
                    #print(word)
                    # Increment the counter
                    count += 1

#ae
print("Count of words with length 6 and no 'a':",len(wordslist))
count = 0
for word in wordslist:
    if word.lower()[4] == 'e':
        count +=1
print("Count of words with length 6 and e at position 5:",count)


#aei
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower():
        count +=1
print("Count of words with length 6 and i not present:",count)

#aeio
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o':
        count +=1
print("Count of words with length 6 and o at position 2:",count)

#aeiou
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o' and 'u' not in word.lower():
        count +=1
print("Count of words with length 6 and u not present:",count)

#aeioub
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o' and 'u' not in word.lower() and 'b' not in word.lower():
        count +=1
print("Count of words with length 6 and b not present:",count)

#aeioubg
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o' and 'u' not in word.lower() and 'b' not in word.lower() and 'g' not in word.lower():
        count +=1
print("Count of words with length 6 and g not present:",count)

#aeioubgd
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o' and 'u' not in word.lower() and 'b' not in word.lower() and 'g' not in word.lower() and 'd' not in word.lower() :
        count +=1
print("Count of words with length 6 and d not present:",count)

#aeioubgdr
count = 0
for word in wordslist:
    if word.lower()[4] == 'e' and 'i' not in word.lower() and word.lower()[1]=='o' and 'u' not in word.lower() and 'b' not in word.lower() and 'g' not in word.lower() and 'd' not in word.lower() and word.lower()[5]=='r':
        count +=1
print("Count of words with length 6 and r at position 6:",count)
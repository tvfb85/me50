import re

# Get user input
text = input("Text: ")

# Sum letters, words, sentences
letters = sum(c.isalpha() for c in text)
words = len(text.split())
sentences = len(re.split('\. |\! |\? ', text))

# Calculate L and S values for Coleman-Liau formula
L = float(letters / words * 100)
S = float(sentences / words * 100)

# Save formula result
idx = round(0.0588 * L - 0.296 * S - 15.8)

# Print grade
if idx < 1:
    print("Before Grade 1")
elif idx > 16:
    print("Grade 16+")
else:
    print(f"Grade {idx}")
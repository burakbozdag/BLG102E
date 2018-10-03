import random
import sys


if len(sys.argv) < 3:
    print("Usage: foo.py text_file sentence")
    sys.exit(1)

filename = sys.argv[1]
with open(filename) as f:
    lines = f.readlines()

word_pos = {}
for i_line, line in enumerate(lines):
    for i_word, word in enumerate(line.split()):
        if word not in word_pos:
            word_pos[word] = []
        word_pos[word].append((i_line, i_word))

current_line = -1
sentence = sys.argv[2]
for word in sentence.split():
    if word not in word_pos:
        print('Word not found: ' + word)
        sys.exit(1)

    choices = word_pos[word]
    line, index = random.choice(choices)
    print(line - current_line, index + 1)
    current_line = line

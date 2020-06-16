import random


def file_prompt():
    while True:
        filename = input("What is the name of the file you want to randomize? (for example: example.txt) ")
        try:
            file = open(filename, 'r')
            return filename, file
        except FileNotFoundError:
            print("File '{}' doesn't exist in current directory!".format(filename))

def randomize(letter: str):
    vowels = "aeiou"
    if letter.lower() not in vowels:
        return letter
    vowels = vowels.upper() if letter.isupper() else vowels
    return random.choice(vowels.replace(letter, ""))

    

if __name__=="__main__":
    filename, file = file_prompt()
    lines = file.readlines()
    file.close()
    output_file = open(filename.replace(".txt", "_output.txt"), "w")
    for line in lines:
        for char in line:
            output_file.write(randomize(char));
    output_file.close()


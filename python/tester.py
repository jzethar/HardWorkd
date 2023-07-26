import csv
import random

present_simple = {
    "yo" :"o",
    "tu" : "as",
    "el" : "a",
    "nosotros" : "amos",
    "vosotros" : "ais",
    "ellos" : "an",
    "vos" : "as"
}

def read_csv_words(filename, encoding='utf-16'):
    translation_dict = {}

    with open(filename, 'r', encoding=encoding) as file:
        reader = csv.DictReader(file)
        for row in reader:
            translation_dict[row['Translation']] = row['Word']

    return translation_dict

def read_csv_verbs(filename, encoding='utf-8'):
    translation_dict = {}

    with open(filename, 'r', encoding=encoding) as file:
        reader = csv.DictReader(file)
        for row in reader:
            translation_dict[row['Translation']] = [row['Word'], row['Rule']]

    return translation_dict

def random_translation(translation_dict):
    translation = random.choice(list(translation_dict.keys()))
    return translation

def parse_verb(verb):
    ### let's try first rule: ar, ir and er are endings and another part is root
    reflex = ""
    ending = verb[-2:]
    if ending == 'se':
        reflex = ending
        ending = verb[-4:-2]
        root = verb[:-4]
    else:
        root = verb[:-2]
    return root, ending, reflex

def conjunction(root, ending, kind, rule = None):
    if rule is None:
        ending = present_simple[kind]
        return root + ending
    
    return ""

def verbs_flow():
    filename = 'verbs.csv'  # Replace with the path to your CSV file
    translation_dict = read_csv_verbs(filename)
    words_to_test = list(translation_dict.keys())
    random.shuffle(words_to_test)

    correct_answers = 0
    wrong_answers = 0

    for translation in words_to_test:
        print(f"Translate: {translation}")
        user_input = input("Enter the corresponding word (or 'q' to quit): ")
        if user_input.lower() == 'q':
            break
    
        root, ending, reflex = parse_verb(translation_dict.get(translation)[0]) # wtf why root is empty
        parsed = conjunction(root, ending, "yo")
        if user_input.lower() == parsed.lower():
            print("Correct!")
            correct_answers += 1
        else:
            print(f"Wrong! The correct word is: {parsed}")
            wrong_answers += 1
        print(translation)

    

def words_flow():
    filename = 'words.csv'  # Replace with the path to your CSV file
    translation_dict = read_csv_words(filename)

    num_words = input("Enter the number of most recent words to be tested on (enter 'all' for all words): ")

    if num_words.lower() == 'all':
        words_to_test = list(translation_dict.keys())
    else:
        num_words = int(num_words)
        words_to_test = list(translation_dict.keys())[-num_words:]

    random.shuffle(words_to_test)

    correct_answers = 0
    wrong_answers = 0

    for translation in words_to_test:
        print(f"Translate: {translation}")
        user_input = input("Enter the corresponding word (or 'q' to quit): ")

        if user_input.lower() == 'q':
            break

        correct_word = translation_dict.get(translation)

        if user_input.lower() == correct_word.lower():
            print("Correct!")
            correct_answers += 1
        else:
            print(f"Wrong! The correct word is: {correct_word}")
            wrong_answers += 1

            for _ in range(5):
                user_input = input("Try again: ")
                if user_input.lower() == correct_word.lower():
                    print("Correct!")
                    correct_answers += 1
                    break
                else:
                    print("Wrong!")
    total_answers = correct_answers + wrong_answers
    if total_answers > 0:
        percentage_correct = (correct_answers / total_answers) * 100
    else:
        percentage_correct = 0

    return correct_answers, wrong_answers, percentage_correct

def main():
    choose_words_verbs = input("Enter '1' - to choose words and '2' - to choose verbs: ")

    if choose_words_verbs == "1":
        correct_answers, wrong_answers, percentage_correct = words_flow()
    if choose_words_verbs == "2":
        verbs_flow()

    score_message = f"Session score: {correct_answers} correct, {wrong_answers} wrong ({percentage_correct:.2f}% correct)"

    score_filename = 'session_score.txt'
    with open(score_filename, 'a') as score_file:
        score_file.write(score_message + "\n")

    print(score_message)
    print("Session completed. Score appended to file.")

if __name__ == "__main__":
    main()

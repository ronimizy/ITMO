from collections import Counter


def editorial_distance(str1, str2):       # редакторское расстояние
    length1 = len(str1)
    length2 = len(str2)
    editor = range(0, length1 + 1)
    for i in range(1, length2 + 1):
        prev = editor
        editor = [i] + [0] * length1
        for j in range(1, length1 + 1):
            ch = prev[j - 1]
            add = prev[j] + 1
            d = editor[j - 1] + 1
            if str1[j - 1] != str2[i - 1]:
                ch += 1
            editor[j] = min(ch, add, d)
    return editor[length1]


def insert_char(str1, ch, idx):           # изменить слово добавлением символа
    if idx >= len(str1):
        result = str1 + ch
        return result
    result = ''
    i = 0
    while i < len(str1):
        if i == idx:
            result += ch
            result += str1[i]
            i += 1
        else:
            result += str1[i]
            i += 1
    return result


def resize_char_to_capital(str1, idx):    # изменить строчную букву на заглавную
    result = ''
    for i in range(len(str1)):
        if i == idx:
            result += str1[i].upper()
        else:
            result += str1[i]
    return result


text_file = open("input_text.txt", "r", encoding="MacCyrillic")
dict_file = open("dict1.txt", "r", encoding="MacCyrillic")
fout = open("corrected_text.txt", "w", encoding="MacCyrillic")
text = text_file.read()
text_copy = text
text = text.replace(".", "")
text = text.replace(",", "")
text = text.replace("?", "")
text = text.replace("!", "")
text = text.replace(":", "")
text = text.replace(";", "")
text = text.replace("(", "")
text = text.replace(")", "")
text = text.replace("»", "")
text = text.replace("«", "")
text = text.replace("{", "")
text = text.replace("}", "")
text = text.replace("—", "")
text = text.replace("–", "")
text = text.lower()
text_list = text.split()
frequency = Counter(text_list)
print("Количество словоформ: ", len(text.split()))       # вывод количества словоформ
print("Количество разных словоформ: ", len(frequency))   # вывод количества разных словоформ

key = []
value = []
for string in dict_file:
    a, b = string.replace("\n", "").split(' ')
    key.append(a)
    value.append(b)
dict_of_dict = {key[i]: value[i] for i in range(len(key))}
text_el = {str1: frequency[str1] for str1 in frequency if str1 in dict_of_dict}
print("Количество разных словоформ, присутствующих в словаре: ", len(text_el))
print("Количество разных словоформ, отсутствующих в словаре: ", len(frequency) - len(text_el))

words_not_in_dict = []      # массив слов, которых нет в словаре
for word in text_list:
    if word not in dict_of_dict:
        words_not_in_dict.append(word)
print("Словоформы, отсутствующие в словаре: ", end='')
print(*words_not_in_dict, sep=", ")
print('\n')

corrected_words_1 = {}      # массив слов, которых нет в словаре, которые можно исправить за 1 операцию
for word in words_not_in_dict:
    for i in range(1, len(word)):
        if word[0:i] in dict_of_dict.keys() and word[i:len(word)] in dict_of_dict.keys():
            temp = corrected_words_1.get(word, [])
            if len(temp) == 0:
                corrected_words_1[word] = [word[0:i], word[i:len(word)], 0]
            elif (frequency[word[0:i]] + frequency[word[i:len(word)]]) > (frequency[temp[0]] + frequency[temp[1]]):
                corrected_words_1[word][0] = word[0:i]
                corrected_words_1[word][1] = word[i:len(word)]
                corrected_words_1[word][2] += 1
    for ch in dict_of_dict.keys():
        if editorial_distance(word, ch) == 1:
            temp = corrected_words_1.get(word, [])
            if len(temp) == 0:
                corrected_words_1[word] = [ch]
            elif len(temp) == 1:
                if frequency[ch] > frequency[temp[0]]:
                    corrected_words_1[word][0] = ch
            elif len(temp) == 2:
                if frequency[ch] > (frequency[temp[0]] + frequency[temp[1]]):
                    corrected_words_1[word] = [ch]

uncorrected_words_1 = []    # массив слов, которых нет в словаре, которые нелья исправить за 1 операцию
for word in words_not_in_dict:
    if word not in corrected_words_1.keys():
        uncorrected_words_1.append(word)

corrected_words_2 = {}      # массив слов, которых нет в словаре, которые можно исправить за 2 операции
for word in uncorrected_words_1:
    for i in range(1, len(word)):
        for ch in dict_of_dict.keys():
            if word[0:i] in dict_of_dict.keys() and editorial_distance(word[i:len(word)], ch) == 1:
                temp = corrected_words_2.get(word, [])
                if len(temp) == 0:
                    corrected_words_2[word] = [word[0:i], ch]
                elif (frequency[word[0:i]] + frequency[ch]) > (frequency[temp[0]] + frequency[temp[1]]):
                    corrected_words_2[word][0] = word[0:i]
                    corrected_words_2[word][1] = ch
            elif editorial_distance(word[0:i], ch) == 1 and word[i:len(word)] in dict_of_dict.keys():
                temp = corrected_words_2.get(word, [])
                if len(temp) == 0:
                    corrected_words_2[word] = [ch, word[i:len(word)]]
                elif (frequency[ch] + frequency[word[i:len(word)]]) > (frequency[temp[0]] + frequency[temp[1]]):
                    corrected_words_2[word][0] = ch
                    corrected_words_2[word][1] = word[i:len(word)]
    for ch in dict_of_dict.keys():
        if editorial_distance(word, ch) == 2:
            temp = corrected_words_2.get(word, [])
            if len(temp) == 0:
                corrected_words_2[word] = [ch]
            elif len(temp) == 1:
                if frequency[ch] > frequency[temp[0]]:
                    corrected_words_2[0] = ch
            elif len(temp) == 2:
                if frequency[ch] > (frequency[temp[0]] + frequency[temp[1]]):
                    corrected_words_2 = [ch]

uncorrected_words_2 = []    # массив слов, которых нет в словаре, которые нельзя исправить за 1 или 2 операции
for word in uncorrected_words_1:
    if word not in corrected_words_2.keys():
        uncorrected_words_2.append(word)

print("Слова исправлены следующим образом:\n")
for word in corrected_words_1.keys():
    print(word, '-', *corrected_words_1[word], '- 1')
print('')
for word in corrected_words_2.keys():
    print(word, '-', *corrected_words_2[word], '- 2')
print('')
for word in uncorrected_words_2:
    print(word, '-', "не найдено", '- >2')

text_copy_list = text_copy.split('\n')       # разбиение исходного текста на массив строк
text_result = ""
for string in text_copy_list:                # обработка каждой строки в исходном тексте
    string_list = string.replace('\n', '').split()
    for word in string_list:                 # обработка каждого слова в строке
        dict_ch = {}
        for ch in range(len(word)):          # обработка каждого символа в слове
            if (word[ch] == '?') or (word[ch] == '!') or (word[ch] == '(') or (word[ch] == ')') or (
                    word[ch] == ':') or (word[ch] == ';') or (word[ch] == '.') or (word[ch] == ',') or (
                    word[ch] == '«') or (word[ch] == '»') or (word[ch] == '}') or (word[ch] == '{'):
                dict_ch[word[ch]] = dict_ch.get(word[ch], [])
                dict_ch[word[ch]].append(ch)
            elif ord(word[ch]) >= 1040 and ord(word[ch]) <= 1071:  # диапазон заглавных русских букв в таблице ASCII
                dict_ch['Upper'] = dict_ch.get('Upper', [])
                dict_ch['Upper'].append(ch)
        word = word.lower()
        word = word.replace("?", "")
        word = word.replace("!", "")
        word = word.replace("»", "")
        word = word.replace("«", "")
        word = word.replace(":", "")
        word = word.replace(";", "")
        word = word.replace(",", "")
        word = word.replace(".", "")
        word = word.replace("(", "")
        word = word.replace(")", "")
        word = word.replace("}", "")
        word = word.replace("{", "")
        if word in corrected_words_1.keys():
            final_word = ''
            for i in range(len(corrected_words_1[word])):
                if i == 0:
                    final_word = str(corrected_words_1[word][i]) + ' '
                else:
                    final_word = str(final_word) + str(corrected_words_1[word][i])
            for ch in dict_ch.keys():
                if ch != 'Upper':
                    for pos in dict_ch[ch]:
                        final_word = insert_char(final_word, ch, pos)
                else:
                    for pos in dict_ch[ch]:
                        final_word = resize_char_to_capital(final_word, pos)
            text_result += final_word + ' '
        elif word in corrected_words_2.keys():
            final_word = ''
            for i in range(len(corrected_words_2[word])):
                if i == 0:
                    final_word = corrected_words_2[word][i] + ' '
                else:
                    final_word = final_word + corrected_words_2[word][i]
            for ch in dict_ch.keys():
                if ch != 'Upper':
                    for pos in dict_ch[ch]:
                        final_word = insert_char(final_word, ch, pos)
                else:
                    for pos in dict_ch[ch]:
                        final_word = resize_char_to_capital(final_word, pos)
            text_result = text_result + final_word + ' '
        else:
            final_word = word
            for ch in dict_ch.keys():
                if ch != 'Upper':
                    for pos in dict_ch[ch]:
                        final_word = insert_char(final_word, ch, pos)
                else:
                    for pos in dict_ch[ch]:
                        final_word = resize_char_to_capital(final_word, pos)
            text_result += final_word + ' '
    text_result = text_result[0:len(text_result) - 1] + '\n'
fout.write(text_result)
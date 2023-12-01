def part1(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    ret = 0
    for line in lines:
        first_digit = -1
        second_digit = -1

        for ch in line:
            if ch.isnumeric():
                if first_digit == -1:
                    first_digit = int(ch) * 10

                second_digit = int(ch)
        ret += first_digit + second_digit

    return ret

def part2(filename):
    with open(filename, 'r') as f:
        lines = f.readlines()
    number_words = {
        'one': 1,
        'two': 2,
        'three': 3,
        'four': 4,
        'five': 5,
        'six': 6,
        'seven': 7,
        'eight': 8,
        'nine': 9,
    }

    ret = 0

    for line in lines:
        first_digit = -1
        second_digit = -1

        for i in range(0, len(line)):
            ch = line[i]
            if ch.isnumeric():
                if first_digit == -1:
                    first_digit = int(ch) * 10
                second_digit = int(ch)
            else:
                for (k, v) in number_words.items():
                    if k in line[i:i+len(k)]:
                        if first_digit == -1:
                            first_digit = v * 10
                        second_digit = v
                        break
        ret += first_digit + second_digit

    return ret

import sys
print(part1(sys.argv[1]))
print(part2(sys.argv[1]))

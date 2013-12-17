import random
import string

ALL_CAHRS = string.ascii_lowercase + string.ascii_uppercase + string.digits


def random_str(str_len):
    return ''.join(random.choice(ALL_CAHRS) for x in range(str_len))


def gen_string_pair():
    common_substring = random_str(random.randint(20, 100))

    random_addition_str = lambda: random_str(random.randint(10, 20))
    str1 = random_addition_str() + common_substring + random_addition_str()
    str2 = random_addition_str() + common_substring + random_addition_str()

    return (str1, str2), common_substring

if __name__ == '__main__':
    result = []

    with open('test_cases.txt', 'w') as f:
        for i in xrange(100):
            (s1, s2), common_substring = gen_string_pair()
            f.write(s1)
            f.write('\n')
            f.write(s2)
            f.write('\n')

            result.append(common_substring)

    with open('result.txt', 'w') as f:
        f.write('\n'.join(result))
        f.write('\n')

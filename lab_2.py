# 211RDB105 Artjoms Kučerjavijs

def input_sequence(list):
    x = int(input())
    while x != 0:
        list.append(x)
        x = int(input())

first, second, res = [], [], []
input_sequence(first)
input_sequence(second)
for first_el in first:
    if not first_el in second:
        res.append(first_el)
for num in res:
    print(num)

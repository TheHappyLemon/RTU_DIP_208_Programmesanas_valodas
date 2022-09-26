# 211RDB105 Artjoms Kučerjavijs
NUMBER_AMOUNT = 3
nums = []
for i in range(NUMBER_AMOUNT):
    nums.append(int(input()))
nums.remove(max(nums))
print(max(nums))
    

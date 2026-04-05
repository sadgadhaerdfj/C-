#求三国演义字符权重
import openpyxl

# 打开并读取《三国演义》文本文件
f = open('三国演义原文.txt', 'r', encoding='utf-8')
character = f.read()
f.close()

# 统计每个字符的出现次数
weight = {}    #创建一个空字典来装三国演义的字符及权重的键值对
for i in range(len(character)):    #循环遍历文本中的每个字符
    if character[i] not in weight:   #检查它是否已经在count1字典中
        weight[character[i]] = character.count(character[i])  #如果不在，就将该字符作为键，
                                                        # 并使用character.count(character[i])方法统计它在整个文本中的出现次数，
                                                        # 然后将该出现次数作为对应键的值存储在weight字典中

# 将统计结果写入文件
f = open('三国演义权重.txt', 'a', encoding='utf-8')
# 打印字典
print(weight)
for i in weight:   #循环遍历weight字典中的键（即每个字符）
    if (i == '\n'):    #如果字符是换行符，则在写入文件时使用"\n"来表示，并且添加相应的缩进
        f.write('\\n' + f"    {weight[i]}" + '\n')
    else:              #如果字符不是换行符，则直接将字符和对应的出现次数写入文件中
        f.write(f"{i}    {weight[i]}" + '\n')
f.close()
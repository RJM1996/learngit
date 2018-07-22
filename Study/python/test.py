
# coding:utf-8

## 类型
#counter = 0
#pi = 3.14
#name = 'rjm'
#
#print counter
#print pi
#print name
#
## 引用
#a = 10
#b = a
#print id(a), id(b), id(10) 
#b = 20
#print id(b), id(20)
#
#b = a
## 代码块和缩进
#if a > b:
#    print "hello"    
#elif a == b:
#    print "haha"
#    print "heihei"
#else:
#    print "hehe"
#
## while 循环
#counter = 0
#while counter < 3:
#    print 'loop %d' % counter
#    counter += 1
#
## for 循环
#str = 'hello'
#for ch in str:
#    print ch
#
#arr = [1, 2, 3, 4]
#for it in arr:
#    print it
#
#a = {
#    'key1' : 'val1' , 
#    'key2' : 'val2' ,
#    'key3' : 'val3'
#}
#for key in a:
#    print key, a[key]
#
#for i in range(0, 10):
#    print i


# 查找 1-99 中第一个 3 的倍数
#for i in range(1, 100):
#    if i % 3 == 0:
#        break
#print i # 这里 i 是全局的, for循环不影响作用域
#
## 查找 1-99 所有 3 的倍数
#for i in range (1, 100):
#    if i % 3 != 0:
#        continue
#    print i

# pass 语句
#x = 11
#if x % 2 == 0:
#    pass
#else:
#    print 'x is prime'

# 列表解析
#a = []
#for x in range(4):
#    a.append(x ** 2)
#print a

#a = [x ** 2 for x in range(4)] # 此处 range 表示的区间是 [0, 4)
#print a
#
#a = [x ** 2 for x in range(100) if x % 2 == 1] # 此处 range 表示的区间是 [0, 100)
#print a


# 函数
#def add(x, y):
#    return x + y
#print add(1, 99)
#print add(-1, -99)
#print add('hello ', 'world') # 拼接字符串
## print add(1, 'hehe') # 报错

# python 不支持重载
# 后定义的覆盖前面的
#def func():
#    print 'hehe'
#
#func()
#
#def func(x):
#    print 'haha'
#
#func(1)
#
#print type(func)

# 默认参数
#def func(x = 10):
#    print x + 10
#func()

# 一个函数返回多个值
# 解包语法
# def GetPoint():
#     x = 10
#     y = 20
#     return x, y
# 
# a, b = GetPoint()
# print a, b
# 
# _, b = GetPoint() # _ 占位符
# print b
# # _*, b = GetPoint() # python3 中的进阶解包语法
# 
# print type(GetPoint()) # tuple 元组类型

# 文件操作
handle = open('./text.txt', 'r')
print type(handle)
# 文件对象可以使用 for 循环遍历
# 凡是可以 for 遍历的对象称为可迭代对象
for line in handle:
    # print line, # 加 , 不打换行
    print line[: -1] # 切片操作
handle.close()

























print '\n\n\n\n'
















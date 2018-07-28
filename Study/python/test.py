#!/usr/bin/python
# coding:utf-8
'''
python 练习
'''
print '\n\n\n\n'
print '\n\n\n\n'

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
# handle = open('./text.txt', 'r')
# print type(handle)
# 文件对象可以使用 for 循环遍历
# 凡是可以 for 遍历的对象称为可迭代对象
# for line in handle:
#     # print line, # 加 , 不打换行
#     print line[: -1] # 切片操作

# 字典的键值对 : 键 对应单词 , 值 对应次数
# data = {}
# for word in handle:
#     word = word[: -1] # 去掉 \n 
#     if word in data:
#         data[word] += 1
#     else:
#         data[word] = 1
# print data
# handle.close()

# 模块
# import add # 导入 add 模块
# print add.Add(1, 20)
# # 会生成 add.pyc 文件, 执行后的二进制文件
# # 模块查找规则: 先从 sys.path 中查找
# import sys
# print sys.path

# 实用函数

# ======================================

# 基础语法

# 缩进规则 建议 4 个空格
# True, False = False, True # 报复社会的做法

# a, b = 10, 20
# print a, b
# a, b = b, a
# print a, b

# 变量的作用域
# globals, locals
# def func():
#     x = 10
#     print locals()
#     print globals()
#     return x
# # print x  # 会报错
# func()


# 文档字符串
# def Add(x, y):
#     '''
#     求两个对象相加的结果
#     '''
#     return x + y

# print Add.__doc__
# help(Add)
# help(type)


# a = 10
# if a >= 10:
#     print 'hello'

# Unix 起始行
# shebang
# print 'hehe'

# 对象和类型
# a = 2
# print id(a)
# print type(a)
# b = 3
# print id(b)
# print type(b)
# b = 2
# print id(b)
# print type(b)

# 标准类型
 
# 其他内建类型
# 类型的类型也是对象
# a = 10
# b = type(a)
# print type(a)
# print type(b)
# # NULL 对象
# print type(None)
# def func():
#     print "hehe"
# print type(func())

# a = 'hehe' # 当做 true
# a = ''     # 空字符串 当做 false
# if a:
#     print '1'
# else:
#     print '2'

# 对象的比较 -- 值 身份 类型
# a = 100
# b = a
# print id(a) == id(b)
# print a < b
# print a > b
# print a is b # is 关键字
# 
# a = 'hehe'
# b = 'heha'
# print a == b
# print id(a) == id(b)
# print a is b # is 关键字
# print type(a) == type(b)
# # 内建函数 isinstance()
# print isinstance(a, type('hehe'))

# 类型工厂函数
# 设计模式之工厂模式
# a = raw_input("> ")
# print int(a) + 10   # int() 工厂函数

# python 不支持指针

# a = 888888888888888888888888888888888888888888
# print type(a) # long 类型 python2 才有
# 
# a = 3.14
# print type(a) # python 只有一种浮点数类型 float

# 数字和运算
# a, b = divmod(10, 3) # 返回商和余数
# print a, b
# a = -1
# print abs(a) # 计算绝对值
# a = 3.1415926
# print round(a, 3) # round() 对浮点数进行四舍五入 , 第二个参数为保留几位小数
# print round(a, 6)
# import math
# print round(math.pi, 10)
# print round(math.pi, 11)
# print round(math.pi, 20) # 最多 11 位
# a = 3.111111111111111111111111111111111111111111111
# print round(a, 11)
# print round(a, 12)

# 条件和循环
# python 使用缩进来匹配代码块
# a = 10
# b = 20
# if a > b:
#     print "hehe"
# else:
#     print "haha"
# 
# x, y, smaller = 3, 4, 1
# if x < y:
#     smaller = x
# else:
#     smaller = y
# 条件表达式
# smaller = x if x < y else y

# else 还可以和 while, for 配合使用
# 只会在循环条件不满足的时候执行 else, break 则不会执行else

# 函数和可调用对象
# def hello():
#     print "hello" # 定义函数
# 
# hello() # 执行函数
# 
# def func1():
#     def func2():
#         print 'hehe'
#     func2() #只能在 func1 中进行调用
#     return func2
# 
# a = func1()
# print a
# a()

# def hello(x):
#     print x
# hello(10)
# hello('hehe')
# hello([1,2,3])
# hello({'a' : 1, 'b' : 2})
# 
# def add(x, y):
#     return x + y
# # print add(10, 'hehe')
# print add(10, 20)
# print add('haha', 'xixi')

# 默认参数
# def Hello(x = 100):
#     print x
# Hello()
# 
# def PrintPoint(x=0, y=0, z=0):
#     print x, y, z
# 
# PrintPoint(10, 12, 14)
# PrintPoint(x=100, z=100) # 关键字参数

# sorted
# a = [9, 5, 2, 7]
# print sorted(a)
# print sorted(a, reverse=True)
# 
# a = [9, -5, 2, 7]
# def cmp(x, y):
#     '根据实际需求自定义排序'
#     if abs(x) < abs(y):
#         return -1
#     elif abs(x) > abs(y):
#         return 1
#     else:
#         return 0
# print sorted(a, cmp=cmp)
# 
# # 参数组 可变参数
# def Log(prefix, *data): # 表示 data 是一个参数组
#     "Log 打印一行日志, 支持多个字段, \t 分割"
#     # split 字符串切分
#     # strtok 字符串切分 http 请求行切分
#     print prefix + '\t'.join(data) # join 把列表元组, 拼接为字符串
# 
# # 日志级别 CRITICAL ERROR WARNING INFO Notice
# Log("[Notice]\t", 'id = 10', 'name = tom', 'score = 100')

# ** 表示字典

# def Log(prefix, **data):
#     print prefix + '\t'.join(data.values())
# 
# Log("[Notice]\t", id = '10', name = 'tom', score = '100')

# 函数重载 ?
# python 不支持函数重载, 因为有更好的方案解决这个问题


def func():
    print '1'
def func():
    print '2'
func()  # 这样后面的函数会覆盖前面的

# 函数返回值
# 没有返回值, 则返回 None 对象

print '\n\n\n\n'
print '\n\n\n\n'

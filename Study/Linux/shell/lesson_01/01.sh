#!/bin/bash

# echo "hello world"

# cat 01.sh
# pwd
# cd ..
# pwd

myint=12
myfloat=3.14
mystring="hello,world"
mychar='c'

# echo $myint
# echo $myfloat
echo "${mystring}hello bit"
# echo $mychar

mystring="world,hello"

echo "${mystring}hello bit"

readonly mystring="hehe"
echo ${mystring}
# mystring="haha"
echo ${mystring}

# unset mystring  # 只读变量不能被删除
echo ${mystring}

echo ${myval}

# 字符串拼接
str1="hello world hehe"
str2="456"
echo $str1$str2"hehe"
echo ${str1}${str2}"hehe"

# 获取字符串长度
echo len=${#str1}
# 提取子字符串
echo ${str1:1:3}
# 查找子字符串
echo `expr index '$str1' hehe`

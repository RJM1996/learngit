#!/system/bin/sh

#================================================================
#   
#   文件名称：test.sh
#   创 建 者：rjm
#   创建日期：2018年06月08日
#   描    述：shell 基本语法
#
#================================================================

# 条件测试
# read myint
# test $myint -eq 100 # 判断从标准输入读到的值是否等于 100
# echo $? # 等于返回 0, 不等于返回 1

# 使用 [ 命令测试
# read myint
# [ $myint -ne 100 ]
# echo $?

# 字符串测试
# read mystring
# [ $mystring == "helloworld" ]
# echo $?

# 字符串判空
# read mystring
# [ -z "$mystring" ]
# [ -n "$mystring" ] # 判定字符串是否非空
# [ "$mystring" == "" ]
# [ x"$mystring" == x ]
# echo $?

# 文件类型测试
# [ -d / ] # 目录
# echo $?
# [ -b /dev/sda ] # 块设备
# echo $?
# [ -c /dev/tty0 ] # 字符设备
# echo $?
# [ -f ./test.sh ] #  普通文件
# echo $?

# 单双引号, 反引号的用法
# string=$PATH
# string='$PATH'
# echo $string

# mystring="hello"
# string="\$mystring"
# echo $string
# string="$mystring"
# echo $string
# string="$mystring"world""
# echo $string
# string="$mystring\"world\""
# echo $string

# mystring=`seq 10`
# echo $mystring
# mystring=`echo "the user number is \`who | wc -l\`"`
# echo $mystring

# TestString="`echo $HOME` `ls .`"
# echo $TestString

# number=$(seq 10)
# echo $number
# 
# TestString=$(echo $HOME $(ls .))
# echo $TestString
# 
# mystring=$(echo "the user number is $(who | wc -l)")
# echo $mystring

# read mystring
# [ ! "$mystring" == "hello" ]
# echo $?

# printf "please enter num1:"
# read num1
# printf "please enter num2:"
# read num2
# [ "$num1" -eq 100 -o "$num2" -eq 200 ]
# echo $?

printf "please enter num1:"
read num1
printf "please enter num2:"
read num2
[ "$num1" -eq 100 -a "$num2" -eq 200 ]
echo $?

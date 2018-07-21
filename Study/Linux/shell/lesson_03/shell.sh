#!/system/bin/sh

#================================================================
#   
#   文件名称：shell.sh
#   创 建 者：rjm
#   创建日期：2018年06月11日
#   描    述：shell 基本语法
#
#================================================================

# if then 语句
# printf "please enter string: "
# read mystring
# if [ X"$mystring" == X"hello" ]; then
# # if [ X"$mystring" == X"hello" ] 
# # then
#     echo "get hello"
# fi

# 条件嵌套
# printf "please enter a random number: "
# read random_num
# if [ "$random_num" -lt 100 ]
# then
#     if [ "$random_num" -eq 50 ]
#     then
#         echo "the num equal 50"
#     elif [ "$random_num" -lt 50 ]
#     then
#         echo "the num less than 50"
#     else
#         echo "the num gt 50 and lt 100"
#     fi
# else
#     echo "the num great than 100"
# fi

# 检测文件中是否包含某关键字
# printf "please enter a file name: "
# read file_name
# if grep -Eq 'hello' "$file_name"; then
#     echo "the file include 'hello'."
# else
#     echo "the file does not include 'hello'."
# fi

# 空语句
printf "please enter string: "
read mystring
if [ "$mystring" == "hello" ]
then
    :
    # false
    # true
else
    echo "not eq"
fi

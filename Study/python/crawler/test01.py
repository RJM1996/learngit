#!/usr/bin/env python
# coding=utf-8

'''
用 BeautifulSoup4 爬虫库 爬小说
'''

import urllib2 # Python 标准库 提供 url 操作方法
import re 
from bs4 import BeautifulSoup # Python 三方库, 提供响应html内容的操作

# 网页获取函数
def OpenPage(url):
    Myheaders = {}
    req = urllib2.Request(url, headers = Myheaders)
    ret = urllib2.urlopen(req)
    data = ret.read()
    return data.decode("GBK", errors="ignore").encode("utf-8")

# 测试网页获取函数
def Test01():
    url = "http://www.shengxu6.com/book/2967.html"
    print OpenPage(url)

# 从主页获取各个章节的 url 
def ParseForMainPage(main_page):
    soup = BeautifulSoup(main_page, "html.parser")
    GetList = soup.find_all(href = re.compile("read"))
    UrlList = []
    for item in GetList:
        UrlList.append("http://www.shengxu6.com" + item["href"])
    return UrlList

def Test02():
    url = "http://www.shengxu6.com/book/2967.html"
    MainPage = OpenPage(url)
    Result = ParseForMainPage(MainPage)
    print type(Result)

# 根据各章的 url 获取各章的内容, 提取标题和正文
def ParseDetailPage(page):
    soup = BeautifulSoup(page, "html.parser")
    Title = soup.find_all(class_ = "panel-heading")[0].get_text()
    Content_tmp = soup.find_all(class_ = "content-body")[0].get_text()
    Content = Content_tmp[0:-12] # 将正文后面的多余字符去掉
    return Title, Content

def Test03():
    url = "http://www.shengxu6.com/read/2967_2008175.html"
    MainPage = OpenPage(url)
    Title, Content = ParseDetailPage(MainPage)
    print Title 
    print Content
    
# 将获取的内容写到文件中
def WriteDataToFile(data):
    with open("output.txt", "a+") as f:
        f.write(data)

def Test04():
    WriteDataToFile("hello, world")

# 将各个步骤连起来
def Test05():
    # url = raw_input("请输入要爬取的小说网址: ")
    url = "http://www.shengxu6.com/book/11492.html"
    MainPage = OpenPage(url)
    UrlList = ParseForMainPage(MainPage)
    print "爬取开始"
    for item in UrlList:
        print "clone: " + item
        details = OpenPage(item)
        Title, Content = ParseDetailPage(details)
        data = "\n\n"+Title+"\n\n"+Content
        WriteDataToFile(data.encode("utf-8"))
    print "爬取完毕"

    
if __name__ == "__main__":
    # Test01()
    # Test02()
    # Test03()
    # Test04()
    Test05()




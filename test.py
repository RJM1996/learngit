#!/usr/bin/env python
# coding=utf-8

import socket

host = 'gitee.com'

try:
    with open('/etc/hosts', 'a+') as fp:
        ip = socket.gethostbyname(host)
        fp.write(' '.join([ip, host, '\n']))
except BaseException as e:
    print(e)
else:
    print('sucess')

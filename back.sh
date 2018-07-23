#!/bin/bash

mycommand=`rsync -a --exclude 'Linux/http/mysql' /home/admin/learngit /mnt/hgfs/CentOS7`
$mycommand

curtime=`date +%Y-%m-%d--%H:%M`
echo $curtime > /home/admin/learngit/time.txt

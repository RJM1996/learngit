mycommand=`rsync -a --exclude 'Linux/http/mysql' /home/rjm/Study /home/rjm/learngit/`
$mycommand

curtime=`date +%Y-%m-%d--%H:%M`
echo $curtime >> /home/rjm/Study/time.txt


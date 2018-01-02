for i in *.txt ; do mv "$i" $(echo $i | sed s/txt/lol/) ; done

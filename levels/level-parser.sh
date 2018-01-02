for i in levels/*.json ; do
    cat "$i" | node levels/level-parser.js > $(echo $i | sed s/json/map/)
done

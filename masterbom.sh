#!/bin/bash

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")
echo '"BOM","#","RefDes","Value","Part"' > tmp/masterbom.csv

#not great, but works
for file in `find . -ipath '*/bom/*.csv'`
do
   sfx=$(echo "$file" | sed -e 's/.*\/\(.*\)\.[cC][sS][vV]/\1/g')
   LC_CTYPE=C && LANG=C && sed -e '/"#"/d' -e '/Part 1/d' -e "s/^/\"${sfx}\",/" "$file"  >> tmp/masterbom.csv
done

IFS=$SAVEIFS


#!/bin/bash
cd $1
for filename in $(find .);
do
    echo $filename;
    diff <(stat -c '%A %F %g %u %s %Y' $filename) <(stat -c '%A %F %g %u %s %Y' $2/$filename);
done

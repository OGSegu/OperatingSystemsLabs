#!/bin/bash
if [ -n "$1" ] && [ -n "$2" ] && [ -n "$3" ] 
	then
	while :	
	do
		now=$(date +"%T")
		echo "$now | Archiving $2 to $1"
		tar -cf $1 $2
		sleep $3
	done
else
	echo "No parameters found."
fi

#!/bin/bash

UPDATE_FILES=("hello_fucking_my_world")
UPDATE_PATH=("/home/pi")

if [ $# -eq 0 ]; then
	echo "usage : %s [address]" $0
	exit 0
fi

echo $1

#scp ./capsuleFW  pi@${#1}:/opt/capsuleFW/bin/capsuleFW 

for (( i = 0 ; i < ${#UPDATE_FILES[@]} ; i++ )) ; do
	echo ${UPDATE_FILES[$i]} ${UPDATE_PATH[$i]} $i
	scp ./${UPDATE_FILES[$i]} root@$1:UPDATE_PATH[$i]
done


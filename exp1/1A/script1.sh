#!/bin/sh
width=40
height=20
function init
{
	clear
	if [ $# -eq 2 ]; then
		width=$1
		height=$2
	fi
}
function display
{
	newLineChar="+"
	spaceChar="-"

	data=`echo $1 | tr '\n', '+'`	#issue

	data=`echo $data | tr " ", "-"`	

	dataIndex=0
	dataLength=${#data}	
	newLineFlag=0

	for (( i=0;i<=height;i++ ))
	do
		for (( j=0;j<=width;j++ ))
		do
			if [ $i -eq 0 ] || [ $i -eq $height ]
			then
				echo -n "#"
			elif [ $j -eq 0 ] || [ $j -eq $width ]
			then
				echo -n "#"
			else
				if [ $dataIndex -lt $dataLength ] && [ $newLineFlag -eq 0 ]
				then
					letter=${data:$dataIndex:1}
					if [ $letter = $spaceChar ]; then
						echo -n " "
					elif [ $letter = $newLineChar ]; then
						echo -n " "
						newLineFlag=1
					else
						echo -n $letter
					fi
					dataIndex=$(( $dataIndex+1 ))
				else
					echo -n " "
				fi
			fi
		done
		echo ;
		newLineFlag=0
	done
}

init

read text
clear

display "$text"

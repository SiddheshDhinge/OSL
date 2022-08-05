#!/bin/bash

function hello
{
	echo "Hello $(whoami)";
	echo "Nice to meet you";
}

function lock
{
	pass="siddhesh";
	echo "Enter password: ";
	read data;

	if [ $pass = $data ];then
		echo $(hello);
	else
		echo "Wrong password";
	fi
}

function table
{
	echo "Enter a number: ";
	read last;
	echo "--------TABLES TILL $last--------";
	num=1;
	inc=1;
	
	while [ $num -le $last ]; do

		mul=$(($num * 10));
	
		while [ $num -le $mul ]; do
			if [ $num -lt 10 ]; then
				echo -n " $num ";
			else
				echo -n "$num ";
			fi;
			let num+=$inc;
		done
		echo " ";
		let inc+=1;
		num=$inc;
	done
}

table;

#!/bin/bash

function hello
{
	echo "Hello $(whoami)";
	echo "Nice to meet you";
}

function table
{
	pass="siddhesh";
	read data;
	flag=[$data == $pass];
	echo $?;
}

table;

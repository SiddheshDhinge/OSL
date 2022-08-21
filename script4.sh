#!/bin/sh

bookName="AddressBook.txt"

newLine()
{
	printf "\n#-----------------------------------------------------------------#\n\n"
}

line()
{
	echo "#-----------------------------------------------------------------#"
}

createBook()
{
	line
	
	echo create book
	
	read bookName
	if [ ${#bookName} -ne 0 ]
	then
		touch "$bookName"
	else
		echo "INVALID NAME"
	fi
}

insertRecord()
{
	line
	printf "Enter Name: "
	read name
	
	printf "Enter Mobile No.: "
	read mobile
	
	printf "Enter Address: "
	read address
	
	printf "Enter Email: "
	read email
	
	printf "Enter Zip Code.: "
	read zcode
	
	printf "%-10.10s %-10.10s %-10.10s %-10.10s %-10.10s\n" "$name" "$mobile" "$address" "$email" "$zcode" >> "$bookName"
}

readRecords()
{
	line
	printf "%-10.10s %-10.10s %-10.10s %-10.10s %-10.10s\n" "NAME" "MOBILE" "ADDRESS" "EMAIL" "ZIP-CODE"
	cat < "$bookName"
}

updateRecord()
{
	printf "Enter Mobile No.: "
	read key
	
	
	
	echo update record
}

deleteRecord()
{
	echo delete record
}

searchRecord()
{
	line
	printf "Enter Mobile No.: "
	read key
	
	printf "%-10.10s %-10.10s %-10.10s %-10.10s %-10.10s\n" "NAME" "MOBILE" "ADDRESS" "EMAIL" "ZIP-CODE"
	grep -wi "$key" "$bookName"
	
	#wait for screen clear
	read x
}


line
while true
do
	echo "MENU"
	echo "1) Create Address Book"
	echo "2) Insert Record"
	echo "3) Read Records"
	echo "4) Update Record"
	echo "5) Delete Record"
	echo "6) Search Record"
	echo "7) Exit"
	printf "Enter Choice: "
	read choice
	
	case $choice in
		1 )	createBook
			;;
		2 )	insertRecord
			;;
		3 )	readRecords
			;;
		4 )	updateRecord
			;;
		5 )	deleteRecord
			;;
		6 )	searchRecord
			;;
		7 )	exit
	esac
	newLine
done

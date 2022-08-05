#!/bin/sh

bookName="AddressBook.txt"
passfile="pass.txt"

newLine()
{
	printf "\n#-----------------------------------------------------------------#\n"
}

line()
{
	echo "#-----------------------------------------------------------------#"
}

menuline()
{
	echo "#~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~#"
}

login()
{
	if [ -f $passfile ]
	then
		echo "Enter Password: "
		read pass
		
		echo "$pass" | md5sum > "copy$passfile"
		pass=`cat copy$passfile`
		rm "copy$passfile"
		
		stored=`cat $passfile`
		
		if [ "$stored" = "$pass" ]
		then
			echo "Welcome $(whoami)"
		else
			echo "Wrong password."
			exit
		fi
	else
		printf "Enter a password: "
		read pass
		
		echo "$pass" | md5sum > "$passfile"
		chmod 444 "$passfile"
	fi
}

createBook()
{
	newLine
	
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
	newLine
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
	
	printf "%-10.10s %-10.10s %-15.15s %-15.15s %-6.6s\n" "$name" "$mobile" "$address" "$email" "$zcode" >> "$bookName"
}

viewRecords()
{
	newLine
	printf "%-10.10s %-10.10s %-15.15s %-15.15s %-8.8s\n" "NAME" "MOBILE" "ADDRESS" "EMAIL" "ZIP-CODE"
	line
	cat "$bookName"
}

updateRecord()
{
	newLine

	printf "Enter Mobile No.: "
	read key

	grep -qwi "$key" "$bookName"

	if [ $? -eq 0 ]
	then
		echo "Record Found."
		echo "Enter New Details: "

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

		edit=`printf "%-10.10s %-10.10s %-15.15s %-15.15s %-6.6s\n" "$name" "$mobile" "$address" "$email" "$zcode"`
		sed -i "s/.*\b$key\b.*/$edit/" "$bookName"
	else
		echo "Record Not Found."
	fi
}

deleteRecord()
{
	newLine
	printf "Enter Mobile No.: "
	read key
	line
	printf "%-10.10s %-10.10s %-15.15s %-15.15s %-8.8s\n" "NAME" "MOBILE" "ADDRESS" "EMAIL" "ZIP-CODE"
	line
	grep -wi "$key" "$bookName"
	if [ $? -eq 0 ]
	then
		echo ;
		sed -i "/.*\b$key\b.*/d" "$bookName"
		echo "Record Found and Deleted"
	else
		echo ;
		echo "Record Not Found"
	fi
}

searchRecord()
{
	newLine
	printf "Enter Mobile No.: "
	read key
	line
	printf "%-10.10s %-10.10s %-15.15s %-15.15s %-8.8s\n" "NAME" "MOBILE" "ADDRESS" "EMAIL" "ZIP-CODE"
	line
	grep -qwi "$key" "$bookName"
	if [ $? -eq 0 ]
	then
		grep -wi "$key" "$bookName"
	else
		echo "Record Not Found."
	fi
}

exitProgram()
{
	echo "Exiting."
	exit
}

main()
{
	login
	while true
	do
		clear
		menuline
		echo "1) Create Address Book"
		echo "2) Insert Record"
		echo "3) View Records"
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
			3 )	viewRecords
				;;
			4 )	updateRecord
				;;
			5 )	deleteRecord
				;;
			6 )	searchRecord
				;;
			7 )	exitProgram
				;;
			* )	printf "Wrong Choice."
		esac
		newLine
		
		read tmp	#waiting for key press
	done
}

#begin here
main

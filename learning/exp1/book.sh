#!/bin/bash
bookFile="book.txt"
touch "$bookFile"
createBook()
{
	printf "Enter Book Name : "
	read book
	if [ ${#book} -ne 0 ]
	then
		bookFile=$book
		touch "$book"
	else
		printf "Error in Name\n"
	fi
}

insert()
{
	printf "Enter Mobile: "
	read mobile

	grep -qwi "^$mobile" "$bookFile"
	
	if [ $? -eq 0 ]
	then
		echo "Already registered."
	else
		printf "Enter Name: "
		read name

		printf "Enter Address: "
		read addr
	
		printf "Enter Email: "
		read email

		printf "Enter Zip: "
		read zipCode

		printf "%-10s %-10s %-10s %-10s %-10s\n" "$mobile" "$name" "$addr" "$email" "$zipCode" >> "$bookFile"
	fi
}

view()
{
	cat "$bookFile"
}

update()
{
	printf "Enter Mobile: "
	read mobile
	
	grep -qwi "^$mobile" "$bookFile"
	
	if [ $? -ne 0 ]
	then
		echo "Wrong mobile no."
	else
		printf "Enter Name: "
		read name

		printf "Enter Address: "
		read addr
	
		printf "Enter Email: "
		read email

		printf "Enter Zip: "
		read zipCode

		newData=`printf "%-10s %-10s %-10s %-10s %-10s\n" "$mobile" "$name" "$addr" "$email" "$zipCode"`
	
		sed -i "s/^$mobile\b.*/$newData/" "$bookFile"
	fi
}

delete()
{
	printf "Enter Mobile: "
	read mobile
	
	grep -qwi "^$mobile" "$bookFile"
	if [ $? -ne 0 ]
	then
		echo "Wrong mobile no."
	else
		sed -i "/^$mobile.*/d" "$bookFile"
		echo "Deletion Success."
	fi
}

search()
{
	printf "Enter mobile: "
	read mobile
	
	grep -qwi "^$mobile" "$bookFile"
	if [ $? -ne 0 ]
	then
		echo "No Such Record."
	else
		grep -wi "^$mobile" "$bookFile"
	fi
}

main()
{
	while [ true ]
	do
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
				2 )	insert
					;;
				3 )	view
					;;
				4 )	update
					;;
				5 )	delete
					;;
				6 )	search
					;;
				7 )	exit
					;;
				* )	echo "Wrong Choice"
					;;
		esac
	done
}

main

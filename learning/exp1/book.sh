#!/bin/bash
bookFile="book.txt"
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
	printf "Enter Name: "
	read name

	printf "Enter Mobile: "
	read mobile

	printf "Enter Address: "
	read addr
	
	printf "Enter Email: "
	read email

	printf "Enter Zip: "
	read zipCode

	printf "%10s %10s %10s %10s %10s\n" "$name" "$mobile" "$addr" "$email" "$zipCode" >> "$bookFile"
}

view()
{
	cat "$bookFile"
}

update()
{
	printf "Enter Name: "
	read name

	printf "Enter Mobile: "
	read mobile

	printf "Enter Address: "
	read addr
	
	printf "Enter Email: "
	read email

	printf "Enter Zip: "
	read zipCode

	newData=`printf "%10s %10s %10s %10s %10s\n" "$name" "$mobile" "$addr" "$email" "$zipCode"`
	
	sed -i "s/.*\b$mobile\b.*/$newData/" "$bookFile"
}

delete()
{
	printf "Enter Mobile: "
	read mobile
	
	sed -i "/.*\b$mobile\b.*/d" "$bookFile"
}

main()
{

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

}
main

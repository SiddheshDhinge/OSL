#!/bin/bash
while true
do
	echo "**************** MENU *************"
	echo "1. Create address book"
	echo "2. insert into address book"
	echo "3. view address book"
	echo "4. delete record"
	echo "5. modify record"
	echo "6. exit"
	echo "Enter your choice :"
	read choice
	if [ $choice == 1 ]
	then
		echo "enter file name :"
		read fname
		touch  $fname
	elif [ $choice == 2 ]
	then
		echo "enter file name you wish to modify :"
		read datafile
		echo "enter data you want to insert :"
		read data
		echo $data >> $datafile
		echo "data inserted successfully"
	elif [ $choice == 3 ]
	then	
		echo "enter file name you wish to view :"
		read file
		echo "data in $file is :"
		cat $file
	elif [ $choice == 4 ]
	then
		echo "enter file name you wish to delete :"
		read dfile
		echo "enter data you want to change :"
		read olddata
		touch temp.txt
		sed "s/$olddata/""/g" $dfile > temp.txt  
		rm $dfile
		mv temp.txt $dfile
	elif [ $choice == 5 ]
	then
		echo "enter file name you wish to modify :"
		read datafile
		echo "enter old data you want to change :"
		read olddata
		echo "enter new data you wish to replace :"
		read newdata
		touch temp.txt
		sed "s/$olddata/$newdata/g" $datafile > temp.txt  
		rm $datafile
		mv temp.txt $datafile
	elif [ $choice == 6 ]
	then
		exit 0 
	else 
		echo "Invalid choice"
	fi
done
	 

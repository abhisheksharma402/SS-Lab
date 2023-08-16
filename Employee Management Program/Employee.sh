#!/bin/sh

CreateEmployee(){
	echo "\nEnter Employee Name: "
	read name
	echo "\nEnter Employee Id: "
	read eid
	echo "\nEnter Employee Phone number: "
	read pno
	if echo "$pno" | grep -P "^[0-9]{10}$"; then

		if grep -P "^.*:$eid:\d{10}$" data.txt; then
			echo "\nRecord with Employee id $eid is already present.\n"
		else	
			echo $name:$eid:$pno >> data.txt
		fi
	else
		echo "\nIncorrect format for phone number."
	fi

}

DeleteRecords(){
	echo "\nEnter the employee id whose record you want to delete: "
	read eid
	if grep -P "^.*:$eid:\d{10}$" data.txt; then
		sed -i "/$eid/d" data.txt
		echo "\nRecord with employee id $eid has been successfully deleted.\n"
	else
		echo "\nRecord with employee id $eid does not exist.\n"
	fi
}


DisplayRecords(){
	echo "\nRecords Found!!\n"
	cat data.txt
	echo "\n"
}


SortRecords(){
	echo "\nEnter the key you want to sort according to (name, id, phone): "
	read key
	if [ "$key" = "name" ]; then
		sort -t ':' -k 1 data.txt
	elif [ "$key" = "id" ]; then
		sort -t ':' -k 2 data.txt
	else
		sort -t ':' -k 3 data.txt
	fi

	echo "\nRecords Sorted by $key successfully."
}


SearchByName(){
	echo "\nEnter the name you want to search for: "
	read name
	if grep "^$name" data.txt; then
		echo "\nRecords Found!!\n"
		grep "^$name" data.txt
	else
		echo "\nNo record for $name exists\n"
	fi

}

SearchById(){
	echo "\nEnter the employee id that you want to search for: "
	read eid
	if grep -P "^.*:$eid:\d{10}$" data.txt; then
		echo "\nRecords Found!!\n"
		grep -P "^.*:$eid:\d{10}$" data.txt
	else
		echo "\n No Record for $eid exists\n"
	fi

}

SearchByPhone(){
	echo "\nEnter the phone number that you want to search for: "
	read pno
	if grep "$pno" data.txt; then
		echo "\nRecords Found!!\n"
		grep "$pno" data.txt
	else
		echo "\n No record for $name exists\n"
	fi
}


Search(){
	choice=0
	exitLoop=0
	while [ $exitLoop -eq 0 ]; do
        	echo "\nMenu:"
        	echo "\n1: Search by employee name"
        	echo "\n2: Search by employee id"

        	echo "\n3: Search by phone number"
		echo "\n4: Exit"

        	echo "\nEnter you Choice (1-4): "
        	read choice
        	case $choice in
                	1)
                        	SearchByName
                        	;;
                	2)
                        	SearchById
                        	;;
                	3)
                        	SearchByPhone
                        	;;
			4)
				return
				;;
			*)
				echo "\nSelect valid choice"
				;;
		esac
	done
					

}

GetEmployeeDetails(){
	Search
}


choice=0
exitLoop=0
while [ $exitLoop -eq 0 ]; do
	echo "\nMenu:"
	echo "\n1: Create a new Employee"
	echo "\n2: Delete an existing employee"
	echo "\n3: Search for an employee"
	echo "\n4: Display Employee Details"
	echo "\n5: Sort Records"
	echo "\n6: List all Records"
	echo "\n7: Exit"

	echo "\nEnter you Choice (1-7): "
	read choice
	case $choice in
		1)
			CreateEmployee
			;;
		2)
			DeleteRecords
			;;
		3)
			Search
			;;
		4)
			GetEmployeeDetails
			;;
		5)
			SortRecords
			;;
		6)
			DisplayRecords
			;;
		7)
			exitLoop=1
			;;
		*)
			echo "\nSelect valid choice"
			;;
	esac
done


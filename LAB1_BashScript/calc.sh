#!/usr/bin/bash

signal=0 # Use to keep looping until the user enter EXIT
res=0	 # Use to store ANS

# An array storing the last 5 successful calculations 
declare -a hist=(
[0]="EMPTY"
[1]="EMPTY"
[2]="EMPTY"
[3]="EMPTY"
[4]="EMPTY"
)
idx=0 # Looping through the array

while [[ $signal == 0 ]] 
do
	# Take user input
	read -p ">> " num1 operator num2

	ch=$operator
	
	# Checking syntax
	if [[ $operator != '+' ]] && [[ $operator != '-' ]] && [[ $operator != '*' ]] && [[ $operator != '/' ]] && [[ $operator != '%' ]] && [[ $operator != '' ]]; then
		echo "SYNTAX ERROR"
		continue
	
	# Cheking if we are dividing by 0
	elif [[ $num2 == 0 && $operator == '/' ]]; then 
		echo "MATH ERROR"
		continue
		
	# Display last 5 calculations
	elif [[ "$num1" == "HIST" ]]; then printf "%s\n" "${hist[@]}"
	
	# Exit the program
	elif [[ "$num1" == "EXIT" ]]; then break	
	elif [[ $num1 != "ANS" ]];
	
	# Perform normal calculation
	then
		if [[ $ch == '+' ]]; then   res=$((num1+num2|bc))
		elif [[ $ch == '-' ]]; then res=$((num1-num2|bc))
		elif [[ $ch == '/' ]]; then res="scale=2; $num1/$num2"
		elif [[ $ch == '%' ]]; then res=$((num1/num2|bc))
		else                        res=$((num1*num2|bc))
		fi
		echo "$res" > ans.log.txt
	
	# Perform calculation with previous answer
	elif [[ $num1 == "ANS" ]];
	then
		filePath="./ans.log.txt"
		res=$(cat "$filePath")
		if [[ $ch == '+' ]]; then   res=$((res+num2|bc))
		elif [[ $ch == '-' ]]; then res=$((res-num2|bc))
		elif [[ $ch == '/' ]]; then res="scale=2; $res/$num2"
		elif [[ $ch == '%' ]]; then res=$((res/num2|bc))
		else                        res=$((res*num2|bc))
		fi
		echo "$res" > ans.log.txt
	fi
	
	# Store the last 5 computation
	if [[ "$num1" != HIST ]]; 
	then
		str1="$num1 "
		str2="$operator "
		str3="$num2"
		str4=" = "
		str5=$(echo "$res" |bc)
		hist[idx]=$str1$str2$str3$str4$str5
		idx=$((idx+1))
		if [[ $idx == 5 ]]; then idx=0
		fi
	fi
	
	# Print out the result
	if [[ "$num1" != HIST ]]; then echo "$res"|bc
	fi
	
	# Clear for another computation
	read cmd
	clear
done


###### Note: There is a limit of this program, if we perform the division with 2 number precision, there will be an error if we use this value as ANS for the next calculation #####

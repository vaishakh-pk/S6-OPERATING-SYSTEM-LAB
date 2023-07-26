Factorial of Number_20220103_Vaishakh.P.K

echo "Enter a number to find the factorial : "
read num

factorial=1

for (( i=1; i<=num; i++ ))
do
  factorial=$((factorial * i))
done

echo "The factorial of $num is $factorial"

Output:
Enter a number to find the factorial : 
5
The factorial of 5 is 120


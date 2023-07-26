Sum of N numbers 20220103_Vaishakh.P.K
#!/bin/bash

echo "Enter the number of inputs: "
read n

sum=0

for (( i=1; i<=$n; i++ ))
do
  sum=$((sum + i))
done

echo "The sum of $n numbers is: $sum"

Output:
Enter the number of inputs: 
5
The sum of 5 numbers is: 15


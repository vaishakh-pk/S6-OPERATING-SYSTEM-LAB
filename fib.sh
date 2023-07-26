Fibonacci Series_20220103_Vaishakh.P.K
#!/bin/bash

echo "Enter the number of terms : "
read n

a=0
b=1

echo "Fibonacci series up to $n terms : "

for (( i=0; i<n; i++ ))
do
  echo -n "$a "
  fib=$((a + b))
  a=$b
  b=$fib
done

Output:
Enter the number of terms : 
5
Fibonacci series up to 5 terms : 
0 1 1 2 3

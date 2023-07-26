String Palindrome 20220103_Vaishakh.P.K
#!/bin/bash

echo "Enter a string: "
read string

# Remove all non-alphanumeric characters and convert to lowercase
string=$(echo "$string" | tr -cd '[:alnum:]' | tr '[:upper:]' '[:lower:]')

# Reverse the string
reverse_string=$(echo "$string" | rev)

# Check if the string is a palindrome
if [ "$string" = "$reverse_string" ]; then
    echo "The string is a palindrome"
else
    echo "The string is not a palindrome"
fi


Output:
Enter a string: 
malayalam
The string is a palindrome


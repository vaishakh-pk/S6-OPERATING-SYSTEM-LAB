// VAISHAKH.P.K
// 20220103

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int isPrime(int number)
{
    if (number <= 1)
        return 0;

    for (int i = 2; i * i <= number; i++)
    {
        if (number % i == 0)
            return 0;
    }

    return 1;
}

int main()
{
    int N;
    printf("Enter the number of values to send: ");
    scanf("%d", &N);

    int fd1[2]; // Parent to child pipe
    int fd2[2]; // Child to parent pipe

    if (pipe(fd1) == -1 || pipe(fd2) == -1)
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork(); // Create a child process

    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
        if (pid == 0)
        {
            // Child process
            close(fd1[1]); // Close the write Enter the number of values to send: 5
            close(fd2[0]); // Close the read end of child to parent pipe

            int receivedNumbers[N];

            read(fd1[0], receivedNumbers, N * sizeof(int));

            int primes[N];
            int primeCount = 0;

            for (int i = 0; i < N; i++)
            {
                if (isPrime(receivedNumbers[i]))
                {
                    primes[primeCount] = receivedNumbers[i];
                    primeCount++;
                }
            }

            write(fd2[1], &primeCount, sizeof(int));
            write(fd2[1], primes, primeCount * sizeof(int));
            close(fd1[0]); // Close the read end of parent to child pipe
            close(fd2[1]); // Close the write end of child to parent pipe
        }
        else
        {
            // Parent process
            close(fd1[0]); // Close the read end of parent to child pipe
            close(fd2[1]); // Close the write end of child to parent pipe

            int numbers[N];

            printf("Enter %d numbers to send: ", N);
            for (int i = 0; i < N; i++)
            {
                scanf("%d", &numbers[i]);
            }

            write(fd1[1], numbers, N * sizeof(int));

            int primeCount;
            read(fd2[0], &primeCount, sizeof(int));

            int primes[primeCount];
            read(fd2[0], primes, primeCount * sizeof(int));

            printf("Prime numbers received from child process: ");
            for (int i = 0; i < primeCount; i++)
            {
                printf("%d ", primes[i]);
            }
            printf("\n");

            close(fd1[1]); // Close the write end of parent to child pipe
            close(fd2[0]); // Close the read end of child to parent pipe
        }

        return 0;
    }
}

// output
/*
Enter the number of values to send: 5
Enter 5 numbers to send: 5
6
2
7
8
Prime numbers received from child process: 5 2 7

*/

#include <stdio.h>
#include <unistd.h>

int main()
{
    int fd[2], n, num, i;
    int buffer[100];
    printf("Total numbers to be passed:\n");
    scanf("%d", &num);

    int array[num];
    printf("Enter the numbers:\n");
    for (i = 0; i < num; i++)
    {
        scanf("%d", &array[i]);
    }

    pipe(fd);
    pid_t p = fork();

    if (p > 0)
    {
        close(fd[0]);
        printf("First\n");
        printf("Parent process\n");
        write(fd[1], &num, sizeof(num));

        for (i = 0; i < num; i++)
        {
            printf("Parent write %d\n", i);
            write(fd[1], &array[i], sizeof(array[i]));
        }
        close(fd[1]);
    }

    if (p == 0)
    {
        close(fd[1]); // Close the unused write end of the pipe
        int elem;
        printf("Second\n");
        printf("Child read\n");
        read(fd[0], &elem, sizeof(elem));

        n = read(fd[0], buffer, sizeof(buffer));

        printf("Received elements in child: ");
        for (i = 0; i < elem; i++)
        {
            printf("%d ", buffer[i]);
        }
        printf("\n");
    }
}

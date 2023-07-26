//VAISHAKH.P.K
//20220103  
//FCFS


#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char process_name[10];
    int arrival_time;
    int burst_time;
} Process;

void fcfs_scheduling(Process processes[], int n) {
    int completion_time[n];
    int waiting_time[n];
    int turnaround_time[n];

    completion_time[0] = processes[0].burst_time;

    for (int i = 1; i < n; i++) {
        int arrival_diff = processes[i].arrival_time - processes[i - 1].arrival_time;
        int burst_time = processes[i].burst_time;
        completion_time[i] = completion_time[i - 1] + arrival_diff + burst_time;
    }

    for (int i = 0; i < n; i++) {
        waiting_time[i] = completion_time[i] - processes[i].burst_time - processes[i].arrival_time;
        turnaround_time[i] = completion_time[i] - processes[i].arrival_time;
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");

    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_name, processes[i].arrival_time,
               processes[i].burst_time, completion_time[i], waiting_time[i], turnaround_time[i]);
    }

    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    double avg_waiting_time = (double) total_waiting_time / n;
    double avg_turnaround_time = (double) total_turnaround_time / n;

    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process processes[n];

    printf("Enter process details:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        printf("Process Name: ");
        scanf("%s", processes[i].process_name);
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

    // Sort the processes by arrival time
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }

    fcfs_scheduling(processes, n);

    return 0;
}

/*

OUTPUT

Enter the number of processes: 4
Enter process details:
Process 1:
Process Name: p1
Arrival Time: 0
Burst Time: 2
Process 2:
Process Name: p2
Arrival Time: 2
Burst Time: 3
Process 3:
Process Name: p3
Arrival Time: 6
Burst Time: 2
Process 4:
Process Name: p4
Arrival Time: 3
Burst Time: 3
Process	Arrival Time	Burst Time	Completion Time	Waiting Time	Turnaround Time
p1	0		2		2		0		2
p2	2		3		7		2		5
p4	3		3		11		5		8
p3	6		2		16		8		10
Average Waiting Time: 3.75
Average Turnaround Time: 6.25

*/

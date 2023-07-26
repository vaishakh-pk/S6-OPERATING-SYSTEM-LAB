//VAISHAKH.P.K
//20220103  
//SJF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char process_name[10];
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
} Process;

void sjf_scheduling(Process processes[], int n) {
    int total_completion_time = 0;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int completed_processes = 0;
    int current_time = 0;
    int smallest_burst_index;

    while (completed_processes < n) {
        smallest_burst_index = -1;
        int smallest_burst = INT_MAX;

        // Find the process with the smallest remaining burst time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time < smallest_burst &&
                processes[i].remaining_time > 0) {
                smallest_burst = processes[i].remaining_time;
                smallest_burst_index = i;
            }
        }

        if (smallest_burst_index == -1) {
            current_time++;
            continue;
        }

        // Execute the process for 1 unit of time
        processes[smallest_burst_index].remaining_time--;
        current_time++;

        if (processes[smallest_burst_index].remaining_time == 0) {
            completed_processes++;
            processes[smallest_burst_index].completion_time = current_time;
            processes[smallest_burst_index].turnaround_time = processes[smallest_burst_index].completion_time -
                                                              processes[smallest_burst_index].arrival_time;
            processes[smallest_burst_index].waiting_time =
                    processes[smallest_burst_index].turnaround_time - processes[smallest_burst_index].burst_time;

            total_completion_time += processes[smallest_burst_index].completion_time;
            total_turnaround_time += processes[smallest_burst_index].turnaround_time;
            total_waiting_time += processes[smallest_burst_index].waiting_time;
        }
    }

    printf("Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_name, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
    }

    double avg_turnaround_time = (double) total_turnaround_time / n;
    double avg_waiting_time = (double) total_waiting_time / n;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
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

        // Set remaining time to burst time initially
        processes[i].remaining_time = processes[i].burst_time;
    }

    sjf_scheduling(processes, n);

    return 0;
}

/*

OUTPUT


Enter the number of processes: 4
Enter process details:
Process 1:
Process Name: p1
Arrival Time: 0
Burst Time: 8
Process 2:
Process Name: p2
Arrival Time: 1
Burst Time: 4
Process 3:
Process Name: p3
Arrival Time: 2
Burst Time: 9
Process 4:
Process Name: p4
Arrival Time: 3
Burst Time: 5
Process	Arrival Time	Burst Time	Completion Time	Turnaround Time	Waiting Time
p1	0		8		17		17		9
p2	1		4		5		4		0
p3	2		9		26		24		15
p4	3		5		10		7		2

Average Turnaround Time: 13.00
Average Waiting Time: 6.50
*/


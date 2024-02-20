#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completed;
};

int find_waiting_time(struct process proc[], int n, int time_quantum) {
    int waiting_time = 0;
    int time = 0;
    int completed = 0;

 
    while (completed != n) {
       
        for (int i = 0; i < n; i++) {
            if (proc[i].arrival_time <= time && proc[i].remaining_time > 0 && !proc[i].completed) {
               
                if (proc[i].remaining_time > time_quantum) {
                    proc[i].remaining_time -= time_quantum;
                    time += time_quantum;
                } else {
                    waiting_time += time - proc[i].arrival_time - proc[i].burst_time;
                    proc[i].completed = 1;
                    proc[i].remaining_time = 0;
                    completed++;
                    time += proc[i].burst_time;
                }
            }
        }
    }

    return waiting_time;
}

int find_turnaround_time(struct process proc[], int n, int waiting_time) {
    int turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        turnaround_time += proc[i].burst_time + waiting_time;
    }
    return turnaround_time;
}

void find_avg_time(struct process proc[], int n, int waiting_time, int turnaround_time) {
    float avg_waiting_time = (float) waiting_time / n;
    float avg_turnaround_time = (float) turnaround_time / n;
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
}

void round_robin_scheduling(struct process proc[], int n, int time_quantum) {
    int waiting_time = find_waiting_time(proc, n, time_quantum);
    int turnaround_time = find_turnaround_time(proc, n, waiting_time);

    printf("Process ID\tBurst Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].burst_time, proc[i].burst_time + waiting_time, waiting_time);
    }

    find_avg_time(proc, n, waiting_time, turnaround_time);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Arrival Time: ");
        scanf("%d", &proc[i].arrival_time);
        proc[i].pid = i + 1;
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].completed = 0;
    }

    round_robin_scheduling(proc, n, time_quantum);

    return 0;
}

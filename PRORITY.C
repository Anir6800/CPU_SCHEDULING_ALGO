#include <stdio.h>

struct process {
    int pid;
    int burst_time;
    int priority;
    int waiting_time;
    int turnaround_time;
};

void find_waiting_time(struct process proc[], int n) {
    proc[0].waiting_time = 0;  
    for (int i = 1; i < n; i++) {
        proc[i].waiting_time = proc[i - 1].waiting_time + proc[i - 1].burst_time;
    }
}

void find_turnaround_time(struct process proc[], int n) {
    for (int i = 0; i < n; i++) {
        proc[i].turnaround_time = proc[i].burst_time + proc[i].waiting_time;
    }
}

void find_avg_time(struct process proc[], int n) {
    float avg_waiting_time = 0, avg_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        avg_waiting_time += proc[i].waiting_time;
        avg_turnaround_time += proc[i].turnaround_time;
    }
    avg_waiting_time /= n;
    avg_turnaround_time /= n;
    printf("Average Waiting Time = %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time = %.2f\n", avg_turnaround_time);
}

void priority_scheduling(struct process proc[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (proc[j].priority < proc[j + 1].priority) {
                struct process temp = proc[j];
                proc[j] = proc[j + 1];
                proc[j + 1] = temp;
            }
        }
    }

    find_waiting_time(proc, n);
    find_turnaround_time(proc, n);

    printf("Process ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].pid, proc[i].burst_time, proc[i].priority,
               proc[i].waiting_time, proc[i].turnaround_time);
    }

    find_avg_time(proc, n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process proc[n];

    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        printf("Burst Time: ");
        scanf("%d", &proc[i].burst_time);
        printf("Priority: ");
        scanf("%d", &proc[i].priority);
        proc[i].pid = i + 1; 
    }

    priority_scheduling(proc, n);

    return 0;
}

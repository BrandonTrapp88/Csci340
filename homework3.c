#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Process status enumeration
enum ProcessStatus {
    INITIALIZING,
    RUNNING,
    SUSPENDED,
    READY,
    TERMINATED
};

// Process structure
struct Process {
    int process_id;
    // Process context
    struct {
        int instruction_pointer;
        int stack_pointer;
        int register_AX;
        int register_BX;
    } context;
    enum ProcessStatus status;
    struct Process* prev;
    struct Process* next;
};

// Function to create a new process
struct Process* createProcess(int process_id, int ip, int sp, int ax, int bx, enum ProcessStatus status) {
    struct Process* newProcess = (struct Process*)malloc(sizeof(struct Process));
    if (newProcess == NULL) {
        perror("Error: Unable to allocate memory for the new process.");
        exit(EXIT_FAILURE);
    }
    newProcess->process_id = process_id;
    newProcess->context.instruction_pointer = ip;
    newProcess->context.stack_pointer = sp;
    newProcess->context.register_AX = ax;
    newProcess->context.register_BX = bx;
    newProcess->status = status;
    newProcess->prev = NULL;
    newProcess->next = NULL;
    return newProcess;
}

// Function to insert a process at the end of the list
void insertProcessEnd(struct Process** head, struct Process* newProcess) {
    if (*head == NULL) {
        *head = newProcess;
    } else {
        struct Process* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newProcess;
        newProcess->prev = current;
    }
}

// Function to display the list of processes
void displayProcesses(struct Process* head) {
    printf("List of Processes:\n");
    struct Process* current = head;
    while (current != NULL) {
        printf("Process ID: %d, Status: %d\n", current->process_id, current->status);
        current = current->next;
    }
}

int main() {
    struct Process* head = NULL;

    // Creating and inserting sample processes
    struct Process* process1 = createProcess(1, 100, 200, 10, 20, RUNNING);
    struct Process* process2 = createProcess(2, 150, 250, 30, 40, READY);
    struct Process* process3 = createProcess(3, 200, 300, 50, 60, TERMINATED);

    insertProcessEnd(&head, process1);
    insertProcessEnd(&head, process2);
    insertProcessEnd(&head, process3);

    // Display the list of processes
    displayProcesses(head);

    // Free memory for processes (cleanup)
    struct Process* current = head;
    while (current != NULL) {
        struct Process* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

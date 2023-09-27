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
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

// Function to read and extract process information from /proc
void readProcessInfo(const char *pid) {
    char path[100];
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    
    FILE *file = fopen(path, "r");
    if (file) {
        char line[100];
        char name[100];
        int ppid;
        unsigned long vsize;

        // Read lines from /proc/<pid>/status file
        while (fgets(line, sizeof(line), file)) {
            if (sscanf(line, "Name:\t%s", name) == 1) {
                // Extract the name of the executable (comm)
                printf("%s (%s)\n", pid, name);
            }
            else if (sscanf(line, "PPid:\t%d", &ppid) == 1) {
                // Extract the parent process id (ppid)
                printf("Parent: %d\n", ppid);
            }
            else if (sscanf(line, "VmSize:\t%lu", &vsize) == 1) {
                // Extract the virtual address space size (vsize)
                printf("VSIZE: %lu KB\n", vsize);
            }
        }
        fclose(file);
    }
}

int main() {
    DIR *dir;
    struct dirent *entry;

    // Open the /proc directory
    dir = opendir("/proc");
    if (dir == NULL) {
        perror("Unable to open /proc");
        exit(EXIT_FAILURE);
    }

    // Read each directory entry (corresponding to a process)
    while ((entry = readdir(dir)) != NULL) {
        if (isdigit(entry->d_name[0])) {
            // Process directory found, read and print process info
            readProcessInfo(entry->d_name);
        }
    }

    closedir(dir);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // Check if the user provided the size of the memory block as a command-line argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <size>\n", argv[0]);
        return 1;
    }

    // Convert the command-line argument (size) to an integer
    int size = atoi(argv[1]);

    // Allocate a block of memory of the specified size
    char *memory_block = (char *)malloc(size);

    // Check if memory allocation was successful
    if (memory_block == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return 1;
    }

    // Set the block to all zeros using memset
    memset(memory_block, 0, size);

    // Print the address of the memory block
    printf("Memory block address: %p\n", (void *)memory_block);

    // Print the contents of the memory block in hexadecimal
    printf("Memory block contents (hexadecimal):\n");
    for (int i = 0; i < size; i++) {
        printf("%02X ", memory_block[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    // Free the allocated memory
    free(memory_block);

    return 0;
}

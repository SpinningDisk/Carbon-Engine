#include <stdio.h>
#include <string.h>

int main() {
    char test[31]; 

    // Get input using fgets, which is safer than scanf for string input
    if (fgets(test, sizeof(test), stdin) != NULL) {
        // Remove trailing newline if present
        size_t len = strlen(test);
        if (len > 0 && test[len - 1] == '\n') {
            test[len - 1] = '\0'; 
        }
    } else {
        fprintf(stderr, "Error reading input.\n");
        return 1; 
    }

    // Print the input 
    printf("You entered: %s\n", test);

    return 0;
}
#include <stdio.h>
#include <string.h>


void checkType(char string[1025]);
int main(){
    extern int ifExit;
    char line[1025];
    // read from the terminal until come across "exit"
    while (ifExit){
        printf(">> ");
        fflush(stdout);
        while (1) { // Infinite loop to ensure a valid input is received
            // Try to read a line; check for empty input
            if (scanf("%[^\n]", line) == 0) {
                printf("INVALID\n");
                while (getchar() != '\n'); // Clear the input buffer
                printf(">> ");
                fflush(stdout);
            } else {
                getchar(); // Consume the newline character left in the input buffer
                break; // Break the loop if input is not empty
            }
        }
        checkType(line);
    }
    return 0;
}

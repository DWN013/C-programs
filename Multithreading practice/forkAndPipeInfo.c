/*
So in the same folder as your .c file to compile, run the following command
$ make

If successful (i.e. gcc didn't complain) you should now have a file name Assignment_1 (with no file extension)

Try running
$./Assignment_1
and see what happens. It should fail with an appropriate error message as this assignment requires an input file from the command line

To run it properly use
$./Assignment_1 sample_in.txt
*/
// Alexander Ukhin, 217946807
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRING_LEN 100
#define MAX_COMMAND_AMNT 500

    void writeOutput(char* command, char* output) // Output function that takes a command string and outputs an output string
    {
        printf("The output of: %s : is\n", command);
        printf(">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
    }
    void stripLineEndings(char *str) {
        int len = strlen(str);
        for (int i = len-1; i > 0; i--) {
            if (str[i] == '\n' || str[i] == '\r') {
                str[i] = 0;
            }
        }
    }

int main(int argc, char *argv[])
{
    char buffer [MAX_COMMAND_AMNT][MAX_STRING_LEN]; // 2D array to store the commands give in the file (up to 100)

    FILE *fpREAD; //reader file pointer
    fpREAD = fopen(argv[1], "r");

    if(fpREAD == NULL){ printf("Can't open file %s for reading.\n", argv[1]); return 1;}

    int cmndAmntCntr = 0; //Total commands written to the array
    while (!feof(fpREAD)){
        fgets(buffer[cmndAmntCntr], MAX_STRING_LEN, fpREAD);
        cmndAmntCntr++;
    }

    fclose(fpREAD); // Close the reader afer finished reading the file
    // --------------------------------------------------
    for(int i = 0; i < (cmndAmntCntr-1); i++){
        int pipefd[2]; // Sets up pipe id size (for 2 items)
        if (pipe(pipefd) == -1){ // If creation of pipe not successful it returns -1
            return 1;
        }
        stripLineEndings(buffer[i]);

        int pid = fork(); // Process ID and create child process

        if (pid < 0) {return 1;} // Return 1 if pipe not created

        // Start execution of commands here
        else if(pid == 0){ // Children pid always == 0
            // Tokenize the command
            char *args[MAX_STRING_LEN];
            char *token = strtok(buffer[i], " ");
            int argCount = 0;
            while (token != NULL) {
                args[argCount++] = token;
                token = strtok(NULL, " ");
            }
            args[argCount] = NULL; // Set last element to NULL as required by exec functions Eg. execlp("ls", "ls", "-F", NULL);

            close(pipefd[0]); // Close read end of the pipe

            dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to write end of pipe

            execvp(args[0], args); // Execute the command

            perror("Exec failed"); // If execvp returns, an error occurred
            return 0;
        }
        else{ // Parent
            waitpid(pid, NULL, 0); // Wait for child to finish
            close(pipefd[1]); // Close writing end of pipe

            int outputStrLen = 999999;
            char output[outputStrLen];
            int bytes_read = read(pipefd[0], output, outputStrLen);
            output[bytes_read] = '\0';

            writeOutput(buffer[i], output);
        }
    }
    return 0;
}

// Make sure file is renamed to 217946807_a01.c.txt

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
// Call the program by ./a.out sample_in.txt
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_STRING_LEN 100
#define MAX_COMMAND_AMNT 500

    // Output function that takes a command string and outputs an output string
    void writeOutput(char* command, char* output)
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
    if(fpREAD == NULL){
            printf("Can't open file %s for reading.\n", argv[1]);
            return 1;
    }

    int cmndAmntCntr = 0; //Total commands written to the array
    while (!feof(fpREAD)){
        fgets(buffer[cmndAmntCntr], MAX_STRING_LEN, fpREAD);
        cmndAmntCntr++;
    }

    fclose(fpREAD); // Close the reader afer finished reading the file

    // --------------------------------------------------
    for(int i = 0; i < (cmndAmntCntr-1); i++){
        int pipefd[2]; // Sets up pipe id size (for 2 items)
        // pipe(fd) creates an anon./unnamed pipe and assigns the file descriptors for the read and write ends of the pipe to the elements of the fd (file descriptor) array
        if (pipe(pipefd) == -1){ // If creation of pipe not successful it returns -1
            return 1;
        }
        stripLineEndings(buffer[i]);
        //printf("\n------------\n%s\n-------------\n", buffer[i]);

        int pid = fork(); // Process ID
        // Create child process
        if (pid < 0) {return 1;} // Return 1 if pipe not created

        // Start execution of commands here
        else if(pid == 0){ // Children pid always == 0
            char *tmp1 = (char*) malloc(sizeof(buffer[i]));
            strcpy(tmp1, buffer[i]);
            char *tmp2 = " ";
            strcat(tmp2, tmp1);
            char *tmp3 = (char*) malloc(sizeof(buffer[i]));
            strcpy(tmp3, buffer[i]);

            char *bufferNoWhiteSpace = strtok(tmp3, " ");
            //strcat(bufferNoWhiteSpace, tmp2);
            close(pipefd[0]); // Close reading end of pipe
            // Get result of command
            // Direct stdout to write end of pipe (used to be 1 instead of STDOUT_FILENO)
            dup2(pipefd[1], STDOUT_FILENO);
            //write(pipefd[1], "Child", 5);
            close(pipefd[1]); // Close writing pipe

            execlp(bufferNoWhiteSpace, NULL);
            perror("Exec failed");
            return 0;
        }
        else{ // Parent
            waitpid(pid, NULL, 0); // Wait for child to finish
            close(pipefd[1]); // Close writing end of pipe
            // Read output of command to screen using given function
            //read(pipefd[0], buffer[i], sizeof(buffer[i]));
            //char* temp = "none\n";

            int outputStrLen = 999999;
            char output[outputStrLen];
            int bytes_read = read(pipefd[0], output, outputStrLen);
            output[bytes_read] = '\0';

            writeOutput(buffer[i], output);
            //printf("%s\n", buffer[i]);
            // execvp(args[0], args);
        }
    }
    return 0;
}

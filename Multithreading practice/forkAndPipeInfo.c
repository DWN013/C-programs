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

    // Output function that takes a command string and outputs an output string
    void writeOutput(char* command, char* output)
    {
        printf("The output of: %s : is\n", command);
        printf(">>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<\n", output);
    }
    // Execute another program in C
    int execFile(int argc, char* argv[])
    {
        //execvp();
    }

int main(int argc, char *argv[])
{
    char buffer [500][MAX_STRING_LEN]; // 2D array to store the commands give in the file (up to 100)

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

    // Close the reader afer finished reading the file
    fclose(fpREAD);


    // --------------------------------------------------
    for(int i = 0; i < cmndAmntCntr; i++){
        int pipefd[2]; // Sets up pipe id size (for 2 items)
        // pipe(fd) creates an anon./unnamed pipe and assigns the file descriptors for the read and write ends of the pipe to the elements of the fd (file descriptor) array
        if (pipe(pipefd) == -1){ // If creation of pipe not successful it returns -1
            return 1;
        }

        int pid = fork(); // Process ID
        // Create child process
        if (pid < 0) {return 1;} // Return 1 if pipe not created

        // Start execution of commands here
        else if(pid == 0){ // Children pid always == 0
            close(pipefd[0]); // Close reading end of pipe
            // Get result of command
            printf("Child = %d\n", i);
            return 0;
        }
        else{ // Parent
            close(pipefd[1]); // Close writing end of pipe
            waitpid(pid, NULL, 0); // Wait for child to finish
            // Read output of command to screen using given function
            int j = i * 2;
            printf("Parent = %d\n", j);
        }
    }
    return 0;
}

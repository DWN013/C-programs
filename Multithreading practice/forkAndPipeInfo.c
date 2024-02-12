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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

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
        //exec();
    }

int main(int argc, char *argv[])
{
    //2D array to store the commands give in the file (up to 100)
    char buffer [500][MAX_STRING_LEN];
    //Process ID
    int pid;
    int fd[2];
    if (pipe(fd) == -1){
        return 1;
    }

    FILE *fpREAD; //reader file pointer
    fpREAD = fopen(argv[1], "r");
    if(fpREAD == NULL){
            printf("Can't open file %s for reading.\n", argv[1]);
            return 1;
    }

    //Total commands written to the array
    int cmndAmntCntr = 0;
    while (!feof(fpREAD)){
        fgets(buffer[cmndAmntCntr], MAX_STRING_LEN, fpREAD);
        cmndAmntCntr++;
    }

    // Close the reader afer finished reading the file
    fclose(fpREAD);

    // --------------------------------------------------
    for(int i = 0; i < cmndAmntCntr; i++){
        // Create child process
        pid = fork();
        // Start execution of commands here





    }
    return 0;
}

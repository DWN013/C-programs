/***********************************
* Filename: marks.c
* Author: Ukhin, Alexander
* Email: alexanderukhin@gmail.com
************************************/

#include <stdio.h>
#include <stdlib.h>

void main( int argc, char *argv[] )
{
    //Steps to process a file
    //1. Declare a file pointer variable
    //2. Open a file using fopen ()
    //3. Process the file using a suitable function
    //4. Close the file using fclose() function

    //arc == argument count, *argv == argument vector (input string from unix line)

    //fopen, fclose, getc (read character from file), putc (write char to file), getw (read int), putw (write int), fprintf (prints formatted input into a file), fscanf (reads formatted input from file),
    //fgets, fputs (write string of chars to file), feof (detects end of file marker)

    //convert string to int
    //for(i = 0; str[i] != '\0'; i++){
    //   currentIndex = str[i] - '0';
    //   num = num * 10 + currentIndex;
    //}

    if (argc != 3){
        printf("Usage: marks [input_file] [output_file]\n");
        return;
    }

    FILE *fpREAD; //reader file pointer
    FILE *fpWRITE;

    fpREAD = fopen(argv[1], "r");
    fpWRITE = fopen(argv[2], "w");

    if(fpREAD == NULL){
        printf("Can't open file %s for reading.\n", argv[1]);
        return;
    }
    if(fpWRITE == NULL){
        printf("Can't open file %s for writing.\n", argv[2]);
        return;
    }

    while (!feof(fpREAD)){

        char firstName [50];
        char lastName [50];
        int ass1Mark;
        int ass2Mark;

        fscanf(fpREAD, "%s %s %d %d", firstName, lastName, &ass1Mark, &ass2Mark);

        float averageMark = (float)((ass1Mark+ass2Mark)/2.0);

        fprintf(fpWRITE, "%s %s %d %d %.1f\n", firstName, lastName, ass1Mark, ass2Mark, averageMark);

    }

    fclose(fpREAD);
    fclose(fpWRITE);

    return;

}  /* end main */

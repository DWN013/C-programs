#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <sys/stat.h>
#include <time.h>
#include <sys/wait.h>
#include <semaphore.h>

void logStart(char* tID);//function to log that a new thread is started
void logFinish(char* tID);//function to log that a thread has finished its time
void startClock();//function to start program clock
long getCurrentTime();//function to check current time since clock was started
time_t programClock;//the global timer/clock for the program

typedef struct thread //represents a single thread, you can add more members if required
{
	char tid[4];//id of the thread as read from file, set in readFile() for you
	unsigned int startTime;//start time of thread as read from file, set in readFile() for you
	int state;//you can use it as per your desire
	pthread_t handle;//you can use it as per your desire; Keeps track of the thread associated each instance of struct thread
	int retVal;//you can use it as per your desire;
} Thread;

//you can add more functions here if required
// Sort threads based on start times
int compareThreads(const void* a, const void* b) {
    Thread* threadA = (Thread*)a;
    Thread* threadB = (Thread*)b;
    return (threadA->startTime - threadB->startTime);
}

//Function to extract the last digit of a string and convert it to an integer
int getEndDigit(char* tid) {
    int len = strlen(tid);
    return tid[len - 1] - '0';
}

// Global variables
sem_t criticalSection;  // Semaphore to control access to critical section
sem_t idSemaphore;      // Semaphore to enforce alternating thread IDs
sem_t idSemaphore2;      // Semaphore to enforce alternating thread IDs
int oddTurn = 0;        // Indicates whether it's an odd or even turn for threads
int first_thread_boolean = 1;   // Flag to indicate first thread being run
int even_count = 0; // Count of threads with even IDs
int odd_count = 0; // Count of threads with odd IDs

void* threadRun(void* t);//the thread function, the code executed by each thread
int readFile(char* fileName, Thread** threads);//function to read the file content and build array of threads


int main(int argc, char *argv[])
{
	Thread* threads = NULL;//remove the comment when you are ready to use it
	int threadCount = -1;

	if (argc != 2) {printf("Wrong amount of arguments"); return 1;} //input file must be accepted as command line argument. You can write the suitable code here to check

	//command line arguments and read the content of the file using readFile().
	//argv[1] to get filename, &threads to use the address of the threads variable
	//"Connects threads read from file with threadCount variable"
    threadCount = readFile(argv[1], &threads);

    if (threadCount < 0) {printf("Error reading threads"); return 1;} //Error condition for no thread generated

	startClock();
	// We have multiple threads so pass in 0 for second argument, 1 for third arg.; Amount of threads running at a time.
    sem_init(&criticalSection, 0, 1);  // Initialize critical section semaphore [MUTEX]
    sem_init(&idSemaphore, 0, 0);      // Initialize ID semaphore, enforces alternating order of thread [ALTERNATE]
    sem_init(&idSemaphore2, 0, 0);      // Initialize ID semaphore, enforces alternating order of thread [ALTERNATE]

    qsort(threads, threadCount, sizeof(Thread), compareThreads); //Sort the threads based on start times


    char *filename = argv[1];
    FILE *file = fopen(filename, "r");
    char *third_chars = malloc(threadCount * sizeof(char));
    for (int i = 0; i < threadCount; i++) {
        char line[1000];
        fgets(line, sizeof(line), file);
        third_chars[i] = line[2];
    }
    fclose(file);

    // Counts amount of odd an even nums
    for (int j = 0; j < threadCount; j++) {
        if((third_chars[j] % 2) == 0){ even_count++; }
        else{ odd_count++; }
    }

    // Start threads
    for (int i = 0; i < threadCount; i++) {
        // All done in seconds
        long startTime = threads[i].startTime;
        long currentTime = getCurrentTime();
        long sleepTime = startTime - currentTime;
        if (sleepTime > 0) { sleep(sleepTime);  // Convert milliseconds to seconds
        }
        // 1st arg: &threads[i].handle specifies address of handle member of i'th thread in threads array
        // 2nd arg: NULL specifies thread attributes
        // 3rd arg: threadRun; The function that the thread will execute once it starts
        // 4th arg: (void*)&threads[i]; Pointer to the data that will be passed to threadRun function when the thread starts
        pthread_create(&threads[i].handle, NULL, threadRun, (void*)&threads[i]);
    }

    // Wait for threads to finish
    for (int i = 0; i < threadCount; i++) { pthread_join(threads[i].handle, NULL); }
    // Free up memory and destroy the semaphores that we are no longer using
    sem_destroy(&criticalSection);
    sem_destroy(&idSemaphore);
    free(threads);

	return threadCount;
}

int readFile(char* fileName, Thread** threads)//do not modify this method
{
	FILE *in = fopen(fileName, "r");

	struct stat st;
	fstat(fileno(in), &st);
	char* fileContent = (char*)malloc(((int)st.st_size+1)* sizeof(char));
	fileContent[0]='\0';
	while(!feof(in))
	{
		char line[100];
		if(fgets(line,100,in)!=NULL)
		{
			strncat(fileContent,line,strlen(line));
		}
	}
	fclose(in);

	char* command = NULL;
	int threadCount = 0;
	char* fileCopy = (char*)malloc((strlen(fileContent)+1)*sizeof(char));
	strcpy(fileCopy,fileContent);
	command = strtok(fileCopy,"\r\n");
	while(command!=NULL)
	{
		threadCount++;
		command = strtok(NULL,"\r\n");
	}
	*threads = (Thread*) malloc(sizeof(Thread)*threadCount);

	char* lines[threadCount];
	command = NULL;
	int i=0;
	command = strtok(fileContent,"\r\n");
	while(command!=NULL)
	{
		lines[i] = malloc(sizeof(command)*sizeof(char));
		strcpy(lines[i],command);
		i++;
		command = strtok(NULL,"\r\n");
	}

	for(int k=0; k<threadCount; k++)
	{
		char* token = NULL;
		int j = 0;
		token =  strtok(lines[k],";");
		while(token!=NULL)
		{

//if you have extended the Thread struct then here
//you can do initialization of those additional members
//or any other action on the Thread members

			if(j==0)
				strcpy((*threads)[k].tid,token);
			if(j==1)
				(*threads)[k].startTime=atoi(token);
			j++;
			token = strtok(NULL,";");
		}
	}
	return threadCount;
}

void logStart(char* tID)
{
	printf("[%ld] New Thread with ID %s is started.\n", getCurrentTime(), tID);
}

void logFinish(char* tID)
{
	printf("[%ld] Thread with ID %s is finished.\n", getCurrentTime(), tID);
}

void* threadRun(void* t)//implement this function in a suitable way
{   Thread* thread = (Thread*)t;
	logStart(thread->tid);

	//Entry section
    // Set boolean flag to indicate that first thread has run (1 == true, 0 == false)
    if (first_thread_boolean) { first_thread_boolean = 0;}

    else if (even_count > 0 && odd_count > 0){
        //while ((getEndDigit(thread->tid) % 2) == (oddTurn % 2) || (odd_count == 0 && even_count > 0) || (even_count == 0 && odd_count > 0)) {
        //while (getEndDigit(thread->tid) % 2 == oddTurn % 2 || (oddTurn != -1 && ((oddTurn % 2 == 0 && even_count > 0) || (oddTurn % 2 == 1 && odd_count > 0)))){

        //printf("%s is now waiting\n", thread->tid);
        if ((getEndDigit(thread->tid) % 2) == 0) {
                sem_wait(&idSemaphore); // Wait for permission based on the alternating order
        } else {
        sem_wait(&idSemaphore2); // Wait for permission based on the alternating order
                    }
    }

    sem_wait(&criticalSection);  // Wait for turn based on ID
    // Critical section starts here
    printf("[%ld] Thread %s is in its critical section\n", getCurrentTime(), thread->tid);
    // Critical section ends here

    sem_post(&criticalSection); // Release criticalSection

    // Update count
    if ((getEndDigit(thread->tid) % 2) == 0){ even_count--; }
    else { odd_count--; }

    if((getEndDigit(thread->tid) % 2) == 0){ sem_post(&idSemaphore2); }
    else { sem_post(&idSemaphore); }



    if(even_count <= 0 || odd_count <= 0){
        if((getEndDigit(thread->tid) % 2) == 0){ sem_post(&idSemaphore2); }
        else { sem_post(&idSemaphore); }
    }

    //printf("Odd count: %d \n Even count: %d \n", odd_count, even_count);

    // Update oddTurn with the last digit of the current thread's ID
    oddTurn = getEndDigit(thread->tid);

    // Exit section
    // sem_post(&idSemaphore); // Signal alternate to allow the next thread
    logFinish(thread->tid);

	return NULL;
}

void startClock() {	programClock = time(NULL); }

long getCurrentTime()//invoke this method whenever you want to check how much time units passed since you invoked startClock()
{
	time_t now;
	now = time(NULL);
	return now-programClock;
}

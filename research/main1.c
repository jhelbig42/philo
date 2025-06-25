#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//a thread excutes a function

void *routine()
{
	printf("Test from Threads\n");
	sleep(3);
	printf("Ending\n");
}

//thread fcnt return int -> use for errorhandling
int	main(int argc, char **argv)
{
	//thread var
	pthread_t	t1, t2;
	//link to funtion executed by thread
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
		return (1);
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
		return (2);
	//wait for the thread
	if (pthread_join(t1, NULL) != 0)
		return (3);
	if (pthread_join(t2, NULL) != 0);
		return (4);


	return (0);
}

// Race Conditions //

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//a thread excutes a function

int	mails = 0;
pthread_mutex_t	mutex;

void *routine()
{
	int i;
	
	i = 0;
	while (i < 100000)
	{
		pthread_mutex_lock(&mutex);
		mails++;
		pthread_mutex_unlock(&mutex);
//read mails
//increment
//write it back to mem
		i++;
	}
	return (NULL);
}

//thread fcnt return int -> use for errorhandling
int	main(int argc, char **argv)
{
	//thread var
	pthread_t	th[4];
	int			i;

	pthread_mutex_init(&mutex, NULL);
	
	i = 0;
	while (i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
			return (1);
		printf("thread %d has started\n", i);
		i++;
	}
	i = 0;
	while (i < 4)
	{	
		if (pthread_join(th[i], NULL) != 0)
			return (3);
		printf("thread %d has terminated\n", i);	
		i++;
	}
	
	pthread_mutex_destroy(&mutex);
	
	printf("Number of Mails: %d\n", mails);

	return (0);
}

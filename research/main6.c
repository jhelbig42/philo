
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int	index;
	
	sleep(1);

	index = *((int *)arg);
	printf("%d\n", primes[index]);
	
	free(arg);

	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	th[10];
	int			i;
	int			*a;

	i = 0;
	while (i < 10)
	{
		a = malloc(sizeof(int));
		*a = i;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
			perror("Failed to join thread");
		i++;
	}
	return (0);
}

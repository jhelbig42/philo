
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>

// building half sums first, sum in main

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void *routine(void *arg)
{
	int	index;
	int	sum;
	int	i;	

	index = *((int *)arg);
	sum = 0;
	i = 0;
	while (i < 5)
	{
		sum += primes[index + i];
		i++;
	}
	//reusing arg
	*((int *)arg) = sum;

	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t	th[10];
	int			i;
	int			*a;
	void		*r;
	int			global_sum;

	i = 0;
	while (i < 2)
	{
		a = malloc(sizeof(int));
		*a = i * 5;
		if (pthread_create(&th[i], NULL, &routine, a) != 0)
			perror("Failed to create thread");
		i++;
	}
	i = 0;
	global_sum = 0;
	while (i < 2)
	{
		if (pthread_join(th[i], &r) != 0)
			perror("Failed to join thread");
		i++;
		global_sum += *((int *)r);
		free(r);
	}
	printf("global_sum: %d\n", global_sum);
	return (0);
}

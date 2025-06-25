
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
//a thread excutes a function


void *roll_dice()
{
	int value;
	int *res;
	
	res = malloc(sizeof(int));

	value = (rand() % 6) + 1;
	*res = value;
	//printf("%d\n", value);
	//printf("Thread result: %p\n", res);
	return ((void *)res);
}

int	main(int argc, char **argv)
{
	srand(time(NULL));

	pthread_t	th[8];
	int			*res[8];
	int			i;

	i = 0;
	while (i < 8)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		if (pthread_join(th[i], (void **)&res[i]) != 0)
			return (3);
		printf("Main res: %d\n", *res[i]);
		i++;
	}
	i = 0;
	while (i < 8)
	{
		free(res[i]);
		i++;
	}
	//free(res);

	return (0);
}

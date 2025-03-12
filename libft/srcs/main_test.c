#include "../include/libft.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac <= 1)
		return (0);
	char	*end;
	char	*testend;
	float test = ft_strtof(av[1], &testend);
	float origin = strtof(av[1], &end);
	printf("result: %f end:%s\n", test, testend);
	printf("origin: %f end:%s\n", origin, end);
	return (0);
}

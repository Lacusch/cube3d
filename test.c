#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "lib/libft/libft.h"

bool	test_charset(char	*str);
bool	could_be_valid(char	*str);

int		main (void)
{
	char	*test1, *test2;
	test1 = "F      244,100,255";
	test2 = "C 22,232,211";
	if (could_be_valid(test1) == false)
		printf("error\n");
	else
		could_be_valid("no error\n");
	return (0);
}

bool	could_be_valid(char	*str)
{
	int	total;
	int size;

	total = 0;
	size = 0;
	if (*str == 'F' || *str == 'C')
		str++;
	else
		return (false);
	while (*str == ' ' && *str)
		str++;
	// printf("str is %s\n", str);
	// printf("str len is %lu\n", ft_strlen(str));
	if (ft_strlen(str) > 11)
	{
		printf("return here\n");
		return (false);
	}
	while (total < 4 && str[total] !='\0')
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break;
	}
	total++;
	int first = total;
	while (total < first + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break;
	}
	total++;
	int secund = total;
	while (total < secund + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break;
	}
	return (true);
}
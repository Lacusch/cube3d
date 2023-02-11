
#include "../includes/cube3d.h"

/*
Add libft and use ft_strlen instead of strlen !	
*/
#include <string.h>

bool	check_extension(char	*av1, char	*extension)
{
	int	file_size;
	int	extension_size;

	file_size = strlen(av1);
	extension_size = strlen(extension);
	while (extension_size > 0)
	{
		if (av1[file_size--] != extension[extension_size--])
		{
			printf("Error\nWrong file extention\n");
			return (true);
		}
	}
	return (false);
}

bool	check_arg(int ac, char **av)
{
	bool	parce_error;

	parce_error = false;
	if (ac != 2)
	{
		if (ac > 2)
		{
			parce_error = true;
			printf("Error\nToo many arguments\n");
		}
		else
		{
			parce_error = true;
			printf("Error\nNo arguments\n");
		}
	}
	else if (check_extension(av[1], ".cub"))
		parce_error = true;
	return (parce_error);
}

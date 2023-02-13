
#include "../includes/cube3d.h"

bool	check_extension(char	*av1, char	*extension)
{
	int	file_size;
	int	extension_size;

	file_size = ft_strlen(av1);
	extension_size = ft_strlen(extension);
	while (extension_size > 0)
	{
		if (av1[file_size--] != extension[extension_size--])
		{
			write(2, WRONG_EXTENSION, ft_strlen(WRONG_EXTENSION));
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
			write(2, TO_MANY_ARGS, ft_strlen(TO_MANY_ARGS));
		}
		else
		{
			parce_error = true;
			write(2, NO_ARGS, ft_strlen(NO_ARGS));
		}
	}
	else if (check_extension(av[1], ".cub"))
		parce_error = true;
	return (parce_error);
}

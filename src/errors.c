
#include "../includes/cube3d.h"

# define META_ERROR "Error\nMissing parameter: "
# define NO_ERROR "Nordern Wall texture\n"
# define SO_ERROR "Southern Wall texture\n"
# define WE_ERROR "Western Wall texture\n"
# define EA_ERROR "Eastern Wall texture\n"
# define FC_ERROR "Floor color texture\n"
# define CC_ERROR "Celling color texture\n"


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
			write(STDERR_FILENO, WRONG_EXTENSION, ft_strlen(WRONG_EXTENSION));
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
			write(STDERR_FILENO, TO_MANY_ARGS, ft_strlen(TO_MANY_ARGS));
		}
		else
		{
			parce_error = true;
			write(STDERR_FILENO, NO_ARGS, ft_strlen(NO_ARGS));
		}
	}
	else if (check_extension(av[1], ".cub"))
		parce_error = true;
	return (parce_error);
}

void	missing_meta(t_cube3d	*data)
{
	write(STDERR_FILENO, META_ERROR, ft_strlen(META_ERROR));
	if (data->NO == NULL)
		write(STDERR_FILENO, NO_ERROR, ft_strlen(NO_ERROR));
	else if (!data->SO)
		write(STDERR_FILENO, SO_ERROR, ft_strlen(SO_ERROR));
	else if (!data->WE)
		write(STDERR_FILENO, WE_ERROR, ft_strlen(WE_ERROR));
	else if (!data->EA)
		write(STDERR_FILENO, EA_ERROR, ft_strlen(EA_ERROR));
	if (data->F_color == NULL)
		write(STDERR_FILENO, FC_ERROR, ft_strlen(FC_ERROR));
	else if (!data->C_color)
		write(STDERR_FILENO, CC_ERROR, ft_strlen(CC_ERROR));
	data->input_error = true;
	data_free(data);
}

bool	invalid_meta(t_cube3d	*data)
{
	//is_everything .png
	//can I open it
	//is color good format?
	(void)data;
	return (false);
}
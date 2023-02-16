
#include "../includes/cube3d.h"

# define META_ERROR "Error\nMissing parameter: "
# define NO_ERROR "Nordern Wall texture\n"
# define SO_ERROR "Southern Wall texture\n"
# define WE_ERROR "Western Wall texture\n"
# define EA_ERROR "Eastern Wall texture\n"
# define FC_ERROR "Floor color texture\n"
# define CC_ERROR "Celling color texture\n"

bool	check_texture_extention(t_cube3d	*data);

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

void	missing_meta(void	*data)
{
	t_cube3d *tmp;

	tmp = (t_cube3d*)data;
	write(STDERR_FILENO, META_ERROR, ft_strlen(META_ERROR));
	if (tmp->NO == NULL)
		write(STDERR_FILENO, NO_ERROR, ft_strlen(NO_ERROR));
	else if (!tmp->SO)
		write(STDERR_FILENO, SO_ERROR, ft_strlen(SO_ERROR));
	else if (!tmp->WE)
		write(STDERR_FILENO, WE_ERROR, ft_strlen(WE_ERROR));
	else if (!tmp->EA)
		write(STDERR_FILENO, EA_ERROR, ft_strlen(EA_ERROR));
	if (tmp->F_color == NULL)
		write(STDERR_FILENO, FC_ERROR, ft_strlen(FC_ERROR));
	else if (!tmp->C_color)
		write(STDERR_FILENO, CC_ERROR, ft_strlen(CC_ERROR));
	tmp->input_error = true;
	data_free(tmp);
}

bool	invalid_meta(t_cube3d	*data)
{
	if (check_texture_extention(data))
		return (true);
	//is_everything .png
	//can I open it
	//is color good format?
	(void)data;
	return (false);
}

bool	check_texture_extention(t_cube3d	*data)
{
	if (check_extension(data->NO, ".png"))
	{
		write(STDERR_FILENO, data->NO, ft_strlen(data->NO));
		write(STDERR_FILENO, " does not end in .png\n", ft_strlen(" does not end in .png\n"));
		return (true);
	}
	return (false);
}
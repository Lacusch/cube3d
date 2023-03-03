/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:23 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/03 14:46:53 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	else if (!can_open(av[1]))
		parce_error = true;
	return (parce_error);
}

void	missing_meta(void	*data)
{
	t_cube3d	*tmp;

	tmp = (t_cube3d *)data;
	write(STDERR_FILENO, META_ERROR, ft_strlen(META_ERROR));
	if (tmp->no == NULL)
		write(STDERR_FILENO, NO_ERROR, ft_strlen(NO_ERROR));
	else if (!tmp->so)
		write(STDERR_FILENO, SO_ERROR, ft_strlen(SO_ERROR));
	else if (!tmp->we)
		write(STDERR_FILENO, WE_ERROR, ft_strlen(WE_ERROR));
	else if (!tmp->ea)
		write(STDERR_FILENO, EA_ERROR, ft_strlen(EA_ERROR));
	if (color_fine(tmp->f_color) == false)
		write(STDERR_FILENO, FC_ERROR, ft_strlen(FC_ERROR));
	else if (color_fine(tmp->c_color) == false)
		write(STDERR_FILENO, CC_ERROR, ft_strlen(CC_ERROR));
	tmp->input_error = true;
	data_free(tmp, EXIT_FAILURE);
}

bool	invalid_meta(t_cube3d	*data)
{
	if (check_texture_extention(data) || !check_can_open(data))
	{
		data->input_error = true;
		return (true);
	}
	return (false);
}

bool	check_texture_extention(t_cube3d	*data)
{
	if (check_extension(data->no, ".png"))
	{
		write(STDERR_FILENO, data->no, ft_strlen(data->no));
		write(STDERR_FILENO, NOT_PNG, ft_strlen(NOT_PNG));
		return (true);
	}
	else if (check_extension(data->so, ".png"))
	{
		write(STDERR_FILENO, data->so, ft_strlen(data->so));
		write(STDERR_FILENO, NOT_PNG, ft_strlen(NOT_PNG));
		return (true);
	}
	else if (check_extension(data->we, ".png"))
	{
		write(STDERR_FILENO, data->we, ft_strlen(data->we));
		write(STDERR_FILENO, NOT_PNG, ft_strlen(NOT_PNG));
		return (true);
	}
	else if (check_extension(data->ea, ".png"))
	{
		write(STDERR_FILENO, data->ea, ft_strlen(data->ea));
		write(STDERR_FILENO, NOT_PNG, ft_strlen(NOT_PNG));
		return (true);
	}
	return (false);
}

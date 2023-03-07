/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:29 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/07 14:41:14 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

bool	open_error(char	*file)
{
	write(STDERR_FILENO, NO_FILE, 22);
	write(STDERR_FILENO, file, ft_strlen(file));
	write(STDERR_FILENO, "\n", 1);
	return (true);
}

void	run_error_func(char	*buff, int fd, void (*func)(void*), void	*data)
{
	free(buff);
	buff = NULL;
	close(fd);
	func(data);
}

bool	invalid_error(void)
{
	write(STDERR_FILENO, INVALID_CHAR, 32);
	return (false);
}

bool	check_can_open(t_cube3d	*data)
{
	int	fd;

	fd = open(data->no, O_RDONLY);
	if (fd == -1)
		return (!open_error(data->no));
	else
		close(fd);
	fd = open(data->so, O_RDONLY);
	if (fd == -1)
		return (!open_error(data->so));
	else
		close(fd);
	fd = open(data->ea, O_RDONLY);
	if (fd == -1)
		return (!open_error(data->ea));
	else
		close(fd);
	fd = open(data->we, O_RDONLY);
	if (fd == -1)
		return (!open_error(data->we));
	else
		close(fd);
	return (true);
}

bool	is_whilespace(char	*c)
{
	if (*c == ' ' || *c == '\t')
		return (true);
	return (false);
}

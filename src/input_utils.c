/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:59 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/07 12:09:51 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../includes/cube3d.h"

int	ft_line(char *map)
{
	int		i;
	char	*tmp;
	int		fd;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
		return (1);
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		i++;
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	return (i);
}

bool	valid_nb(int number)
{
	if (number >= 0 && number <= 255)
		return (true);
	return (false);
}

void	terminate_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	str[i] = '\0';
}

bool	meta_full(t_cube3d	*data)
{
	if (data->no && data->so && data->we && data->ea \
		&& color_fine(data->f_color) && color_fine(data->c_color))
		return (true);
	return (false);
}

bool	color_fine(int color[3])
{
	if (!valid_nb(color[0]))
		return (false);
	if (!valid_nb(color[1]))
		return (false);
	if (!valid_nb(color[2]))
		return (false);
	return (true);
}

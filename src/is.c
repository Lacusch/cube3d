/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:49 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 14:49:36 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

bool	is_closed(char	**map, t_map *map_data)
{
	int	line;

	line = 0;
	if (ft_strchr((map[line]), '0') != NULL)
	{
		write(STDERR_FILENO, NOT_CLOSED, 25);
		return (false);
	}
	while (line < map_data->height)
	{
		if (map[line][0] == '0' || map[line][map_data->width] == '0')
		{
			write(STDERR_FILENO, NOT_CLOSED, 25);
			return (false);
		}
		line++;
	}
	line--;
	if (ft_strchr((map[line]), '0') != NULL)
	{
		write(STDERR_FILENO, NOT_CLOSED, 25);
		return (false);
	}
	return (true);
}

bool	is_valid_nb_quete(char	*buff)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (buff[i] == 'F' || buff[i] == 'C')
		i++;
	while (buff[i] == ' ' && buff[i])
		i++;
	while (buff[i])
	{
		if (buff[i] == ',')
			count++;
		i++;
	}
	if (count != 2)
	{
		write(STDIN_FILENO, INV_QUETE, 39);
		return (false);
	}
	return (true);
}

bool	is_valid_place_quete(char	*buff)
{
	(void)buff;
	return (true);
}

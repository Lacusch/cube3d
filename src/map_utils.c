/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:37 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 13:30:38 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	get_max_width(char	**map)
{
	int	max_width;
	int	i;

	i = 0;
	max_width = 0;
	while (map[i])
	{
		if (ft_strlen(map[i]) > (size_t)max_width)
			max_width = ft_strlen(map[i]);
		i++;
	}
	return (max_width);
}

bool	is_rectange(char	**map, int max_width)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != max_width)
		{
			return (false);
		}
		i++;
	}
	return (true);
}

void	make_recktange(char	**map, int max_width)
{
	int		i;

	i = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) != max_width)
			fill_string(&map[i], max_width);
		i++;
	}
}

void	fill_string(char	**str_add, int max_width)
{
	char	*new_string;
	int		i;
	char	*str;

	str = *str_add;
	i = 0;
	new_string = malloc((sizeof(char)) * max_width + 1);
	while (str[i])
	{
		new_string[i] = str[i];
		i++;
	}
	while (i < max_width)
	{
		new_string[i] = ' ';
		i++;
	}
	new_string[i] = '\0';
	free(str);
	*str_add = new_string;
}

void	player_position_sub(t_cube3d *data, int line)
{
	int		j;
	char	**m_data;

	j = 0;
	m_data = data->map;
	while (m_data[line][j] != '\0')
	{
		if (m_data[line][j] == data->start)
		{
			data->player.x = j;
			data->player.y = line;
		}
		j++;
	}
}

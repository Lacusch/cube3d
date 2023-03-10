/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:35:54 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/10 19:47:22 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	is_same_str(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	if (!ft_strlen(str1) || !ft_strlen(str2))
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	cast_int(float num)
{
	return ((int)(num));
}

bool	has_zero(char		**matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return (false);
	while (matrix[i] != NULL)
	{
		if (ft_strchr(matrix[i], '0') != NULL)
			return (true);
		i++;
	}
	return (false);
}

t_map	get_space(char	**matrix)
{
	int		i;
	int		j;
	t_map	xy;

	xy.height = -1;
	xy.width = -1;
	i = 0;
	j = 0;
	while (matrix[i] != NULL)
	{
		while (matrix[i][j])
		{
			if (matrix[i][j] == '0')
			{
				xy.height = i;
				xy.width = j;
				return (xy);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (xy);
}

bool	check_position(t_player	*player, t_map *map)
{
	(void)map;
	if (player->x == 0 || player->y == 0 || \
		player->x + 1 == map->width || player->y + 1 == map->height)
		return (true);
	return (false);
}

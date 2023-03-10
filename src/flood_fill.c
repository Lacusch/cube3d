/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:06 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/10 16:42:39 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	fill4(char **map, t_map *dimensions, int x, int y)
{
	if (y < 0 || y >= dimensions->height || x < 0 || x >= dimensions->width)
		return ;
	if (map[y][x] != '0' && map[y][x] != 'N'
	&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W')
		return ;
	map[y][x] = 'F';
	fill4(map, dimensions, x + 1, y);
	fill4(map, dimensions, x - 1, y);
	fill4(map, dimensions, x, y + 1);
	fill4(map, dimensions, x, y - 1);
}

void	fill8(char **map, t_cube3d *data, int x, int y)
{
	t_map	*dimensions;

	dimensions = malloc(sizeof(dimensions));
	(*dimensions).height = data->map_data.height;
	(*dimensions).width = data->map_data.width;
	if (y < 0 || y >= dimensions->height || x < 0 || x >= dimensions->width
		|| data->input_error)
		return (free(dimensions));
	if (map[y][x] == ' ')
		return (set_error(data), invalid_map(), free(dimensions));
	if (map[y][x] != '0' && map[y][x] != 'N'
	&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W')
		return (free(dimensions));
	map[y][x] = 'F';
	fill8(map, data, x + 1, y + 1);
	fill8(map, data, x + 1, y);
	fill8(map, data, x + 1, y - 1);
	fill8(map, data, x, y + 1);
	fill8(map, data, x, y - 1);
	fill8(map, data, x - 1, y + 1);
	fill8(map, data, x -1, y);
	fill8(map, data, x - 1, y - 1);
	free(dimensions);
}

void	flood_fill(char **map, t_cube3d *data, int player_x, int player_y)
{
	t_map	map2;

	fill8(map, data, player_x, player_y);
	while (has_zero(map) == true && data->input_error != 1)
	{
		map2 = get_space(map);
		fill8(map, data, map2.width, map2.height);
	}
}

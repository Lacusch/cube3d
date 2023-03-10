/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:16 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/10 19:29:34 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	get_map(t_cube3d	*data, char	*buff, int fd)
{
	char	*tmp;
	char	*tmp2;

	if (!data->input_error)
	{
		check_buffer(buff, data);
		tmp = ft_strdup("");
		while (buff && ft_strncmp(buff, "\n", SIZE_T_MAX) == 0)
		{
			free(buff);
			buff = get_next_line(fd);
		}
		while (buff && !data->input_error)
		{
			if (ft_strncmp(buff, "\n", 2) == 0)
				return (free_close(fd, buff, tmp), set_error(data), el());
			tmp2 = tmp;
			tmp = ft_strjoin(tmp2, buff);
			free_close(-1, tmp2, buff);
			buff = get_next_line(fd);
		}
		data->map = ft_split(tmp, '\n');
		free_close(fd, tmp, buff);
	}
	check_map(data);
}

void	check_map(t_cube3d	*data)
{
	if (data->input_error)
		return ;
	map_valid_chars(data);
	test_map(data);
}

void	map_valid_chars(t_cube3d	*data)
{
	int		i;

	i = 0;
	if (data->map == NULL)
		return (set_error(data));
	while (data->map[i] != NULL)
	{
		if (invalid_line(data->map[i], data) == true)
			return (set_error(data));
		i++;
	}
	if (data->start == '\0')
		no_player(data);
}

/**
 * @brief Test to see if the map is valid
 * @param data main struct holding the map
 */
void	test_map(t_cube3d	*data)
{
	char		**matrix;

	if (data->input_error)
		return ;
	data->map_data.width = get_max_width(data->map);
	if (!is_rectange(data->map, data->map_data.width))
		make_recktange(data->map, data->map_data.width);
	matrix = matrix_dub(data->map);
	data->map_data.height = matrix_size(matrix);
	if (!is_closed(matrix, &(data->map_data)))
		return (set_error(data), matrix_free(matrix));
	player_position(data);
	if (check_position(&data->player, &data->map_data) == 1)
		return (invalid_map(), matrix_free(matrix), set_error(data));
	if (data->map_data.height < 3 || data->map_data.width < 3)
	{
		write (STDERR_FILENO, SMALL_MAP, 23);
		matrix_free(matrix);
		return (set_error(data));
	}
	flood_fill(matrix, data, data->player.x, data->player.y);
	matrix_free(matrix);
}

void	player_position(t_cube3d *data)
{
	int	i;

	i = 0;
	while (i < data->map_data.height)
	{
		player_position_sub(data, i);
		i++;
	}
}

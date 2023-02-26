#include "../includes/cube3d.h"

void	get_map(t_cube3d	*data, char	*buff, int fd)
{
	char	*tmp;
	char	*tmp2;

	if (!data->input_error)
	{
		printf("get_map here\n");
		check_buffer(buff, data);
		tmp = ft_strdup("");
		while (buff && !data->input_error)
		{
			tmp2 = tmp;
			tmp = ft_strjoin(tmp2, buff);
			free(tmp2);
			free(buff);
			buff = get_next_line(fd);
		}
		data->map = ft_split(tmp, '\n');
		free(tmp);
		free(buff);
		close(fd);
	}
	check_map(data);
	if (!data->input_error)
		data_printf(data);
}

void	check_map(t_cube3d	*data)
{
	map_valid_chars(data);
	test_map(data);
}

void	map_valid_chars(t_cube3d	*data)
{
	char	player;
	int		i;

	i = 0;
	player = '\0';
	(void)player;
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
 * 
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
	player_position(data);
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

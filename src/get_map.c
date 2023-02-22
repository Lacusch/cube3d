#include "../includes/cube3d.h"

void	player_position(t_cube3d *data);
void	player_position_sub(t_cube3d *data, int line);


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
 * @todo 1. run floodfill on the duplicate of map and check if everything is closed of or not
 * @todo 2. free and set / print error if something is wrong
 */
void	test_map(t_cube3d	*data)
{
	char		**matrix;

	if (data->input_error)
		return ;
	matrix = matrix_dub(data->map);
	data->map_data.width = get_max_width(matrix);
	if (!is_rectange(matrix, data->map_data.width))
		make_recktange(matrix, data->map_data.width);
	data->map_data.height = matrix_size(matrix);
	player_position(data);
	// flood_fill(matrix, &(data->map_data), data->player.x, data->player.y);
	/*
	if (flood_fill(matrix, &map, player.x, player.y))
	{
		data->input_error = true;
		map_error();
	}
	*/
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
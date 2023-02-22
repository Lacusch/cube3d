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
	// if (!data->input_error)
	// 	data_printf(data);
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
 * 
 * @todo 1. get the max width of the map and store it in a struct
 * @todo 2. fill each string with spaces to get to the max witdh (recktange)
 * @todo 3. get the height of the matrix
 * @todo 4. run floodfill on the duplicate of map and check if everything is closed of or not
 * @todo 5. free and set / print error if something is wrong
 */
void	test_map(t_cube3d	*data)
{
	char		**matrix;
	t_map		map;
	t_player	player;

	if (data->input_error)
		return ;
	matrix = matrix_dub(data->map);
	map.width = get_max_width(matrix);
	if (!is_rectange(matrix, map.width))
		make_recktange(matrix, map.width);
	map.height = matrix_size(matrix);
	/*
	if (flood_fill(matrix, &map, player.x, player.y))
	{
		data->input_error = true;
		map_error();
	}
	*/
	matrix_free(matrix);
	(void)&player;
	(void)&map;
}
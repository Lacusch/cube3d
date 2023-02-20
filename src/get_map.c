#include "../includes/cube3d.h"

void	test_map(t_cube3d	*data);

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
	// fill_map(data->map);
	if (data->input_error)
		return ;
	(void)data;
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

void	test_map(t_cube3d	*data)
{
	// char	**matrix;

	// matrix = matrix_dub(data->map);
	// matrix_printf(matrix);
	// matrix_free(matrix);

	/*
	Duplicate the map
	Get each line to the same lenght (fill it with -1)
	Get length and width
	Flood fill (4 way)
	*/
}
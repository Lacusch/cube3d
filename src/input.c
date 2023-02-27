
#include "../includes/cube3d.h"

void	input_data(t_cube3d	*data, char	*map)
{
	int		fd;
	char	*buff;
	int		i;

	i = 0;
	buff = NULL;
	fd = open(map, O_RDWR);
	buff = get_next_line(fd);
	while (buff && !data->input_error && !meta_full(data))
	{
		check_buffer(buff, data);
		str_free(buff);
		buff = get_next_line(fd);
		i++;
	}
	if (!meta_full(data) && data->input_error == false)
		run_error_func(buff, fd, missing_meta, (void *)data);
	else if (invalid_meta(data) && data->input_error == false)
		free_close(buff, fd);
	else
		get_map(data, buff, fd);
}

void	check_buffer(char	*line, t_cube3d	*data)
{
	if (line[0] == 'N' && line[1] == 'O')
		handle_no(data, line);
	else if (line[0] == 'S' && line[1] == 'O')
		handle_so(data, line);
	else if (line[0] == 'W' && line[1] == 'E')
		handle_we(data, line);
	else if (line[0] == 'E' && line[1] == 'A')
		handle_ea(data, line);
	else if (line[0] == 'F' || line[0] == 'C')
	{
		could_be_valid(line, data);
		if (data->input_error == true)
			return ;
		handle_color(data, line);
	}
}

void	get_rgb_floor(int start, t_cube3d	*data, char *buff, int loop)
{
	int		i2;
	char	*tmp;

	tmp = NULL;
	i2 = 0;
	if (loop != 0)
		buff++;
	while (i2 < 3 && ft_isdigit(buff[start + i2]) && buff)
			i2++;
	tmp = ft_substr(buff, start, i2);
	data->f_color[loop] = ft_atoi(tmp);
	free(tmp);
	if (!valid_nb(data->f_color[loop]))
	{
		invalid_rgb(data);
		return ;
	}
	if (loop != 2 && !data->input_error)
		get_rgb_floor(start + i2, data, buff, ++loop);
}

void	get_rgb_celling(int start, t_cube3d *data, char *buff, int loop)
{
	int		i2;
	char	*tmp;

	tmp = NULL;
	i2 = 0;
	if (loop != 0)
		buff++;
	while (i2 < 3 && ft_isdigit(buff[start + i2]) && buff)
			i2++;
	tmp = ft_substr(buff, start, i2);
	data->c_color[loop] = ft_atoi(tmp);
	free(tmp);
	if (!valid_nb(data->c_color[loop]))
	{
		invalid_rgb(data);
		return ;
	}
	if (loop != 2 && !data->input_error)
		get_rgb_celling(start + i2, data, buff, ++loop);
}

void	free_close(char	*buff, int fd)
{
	free(buff);
	buff = NULL;
	close(fd);
}
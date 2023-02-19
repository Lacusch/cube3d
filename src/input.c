
#include "../includes/cube3d.h"

bool	invalid_error(void);
void	get_map(t_cube3d	*data, char	*buff, int fd);
void	free_close(char	*buff, int fd);

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
	else if (line[0] == 'F')
	{
		terminate_str(line);
		if (could_be_valid(line) == false)
			data->input_error = true;
		else
			handle_color(data, line);
	}
	else if (line[0] == 'C')
	{
		terminate_str(line);
		if (could_be_valid(line) == false)
			data->input_error = true;
		else
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

bool	could_be_valid(char	*str)
{
	int	total;
	int	size;

	total = 0;
	size = 0;
	if (*str == 'F' || *str == 'C')
		str++;
	else
		return (false);
	while (*str == ' ' && *str)
		str++;
	if (ft_strlen(str) > (size_t)11)
	{
		printf("%s", RGB_LONG);
		return (false);
	}
	while (total < 4 && str[total] != '\0')
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
			return (invalid_error());
		if (str[total] == ',')
			break ;
	}
	total++;
	int	first = total;
	while (total < first + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
			return (invalid_error());
		if (str[total] == ',')
			break ;
	}
	total++;
	int	secund = total;
	while (total < secund + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',' || str[total] == '\0')
			total++;
		else
			return (invalid_error());
		if (str[total] == ',')
			break ;
	}
	return (true);
}

void	get_map(t_cube3d	*data, char	*buff, int fd)
{
	if (!data->input_error)
	{
		printf("get_map here\n");
		data_printf(data);
	}
	free(buff);
	close(fd);
	(void)data;
	(void)buff;
	(void)fd;
}

void	free_close(char	*buff, int fd)
{
	free(buff);
	buff = NULL;
	close(fd);
}

void	invalid_rgb(t_cube3d	*data)
{
	write(STDERR_FILENO, INVALID_RGB, 19);
	data->input_error = true;
}

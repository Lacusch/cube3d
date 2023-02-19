
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
		free(buff);
		buff = NULL;
		buff = get_next_line(fd);
		i++;
	}
	if (!meta_full(data) && data->input_error == false)
		run_error_func(buff, fd, missing_meta, (void *)data);
	else if (invalid_meta(data) && data->input_error == false)
	{
		free(buff);
		close(fd);
	}
	else
	{
		printf("get_map here\n");
		if (!data->input_error)
			data_printf(data);
		free(buff);
	}
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
		{
			data->F_color = ft_strdup(line + 2);
			handle_color(data, line);
		}
	}
	else if (line[0] == 'C')
	{
		handle_color(data, line);
		data->C_color = ft_strdup(line + 2);
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
	if (*buff == '-')
	{
		printf("%i is invalid RGB, can not be negative\n", data->f_color[loop]);
		data->input_error = true;
		return ;
	}
	while (i2 < 3 && ft_isdigit(buff[start + i2]) && buff)
			i2++;
	tmp = ft_substr(buff, start, i2);
	data->f_color[loop] = ft_atoi(tmp);
	free(tmp);
	if (!valid_nb(data->f_color[loop]))
	{
		printf("%i is invalid RGB\n", data->f_color[loop]);
		data->input_error = true;
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
		printf("%i is invalid RGB\n", data->c_color[loop]);
		data->input_error = true;
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
		printf("string too big\n");
		return (false);
	}
	while (total < 4 && str[total] != '\0')
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break ;
	}
	total++;
	int first = total;
	while (total < first + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break;
	}
	total++;
	int	secund = total;
	while (total < secund + 3)
	{
		if (ft_isdigit(str[total]) || str[total] == ',' || str[total] == '\0')
			total++;
		else
		{
			printf("invalid character\n");
			return (false);
		}
		if (str[total] == ',')
			break ;
	}
	return (true);
}

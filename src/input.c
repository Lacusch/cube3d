
#include "../includes/cube3d.h"

void	check_buffer(char	*line, t_cube3d	*data);
bool	meta_full(t_cube3d	*data);
int		ft_line(char *map);
bool	is_whilespace(char	*c);
void	handle_no(t_cube3d *data, char	*line);
void	run_error_func(char	*buff, int fd, void(*func)(void*), void	*data);
void	handle_so(t_cube3d *data, char	*line);
void	handle_we(t_cube3d *data, char	*line);
void	handle_ea(t_cube3d *data, char	*line);
void	handle_color(t_cube3d	*data, char *buff);
bool	valid_nb(int	number);
void	get_rgb_floor(int	start, t_cube3d	*data, char	*buff, int loop);
void	invalid_rgb(char	*str, t_cube3d	*data, int loop);
void	get_rgb_celling(int	start, t_cube3d	*data, char	*buff, int loop);

void	input_data(t_cube3d	*data, char	*map)
{
	int		fd;
	char	*buff;

	int i = 0;
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
		run_error_func(buff, fd, missing_meta, (void*)data);
	else if (invalid_meta(data) && data->input_error == false)
	{
		free(buff);
		close(fd);
	}
	else
	{
	//get_map
	// char	*tmp;
	// tmp = ft_strdup("");
	
	// while (buff && !data->input_error)
	// {
	// 	buff = ft_strjoin(buff, ("9"));
	// 	tmp = ft_strjoin(tmp, buff);
	// 	check_buffer(buff, data);
	// 	free(buff);
	// 	buff = get_next_line(fd);
	// }
	// printf("map line is %d\n", ft_line(map) - i);
	// data->map = ft_split(tmp, '9');
	// free(tmp);
	if (!data->input_error)
		data_printf(data);
	free(buff);
	// free(tmp);
	// close (fd);
	}
}

void	check_buffer(char	*line, t_cube3d	*data)
{
//Handle color well
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
		invalid_rgb(line, data, 0);
		if (data->input_error)
		{
			printf("invalid rgb for floor color\n");
			data->input_error = true;
		}
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

bool	meta_full(t_cube3d	*data)
{
	if (data->NO && data->SO && data->WE && data->EA && data->F_color && data->C_color)
		return (true);
	return (false);
}

int	ft_line(char *map)
{
	int		i;
	char	*tmp;
	int		fd;

	i = 0;
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		printf("the file desriptor is:%i\n", fd);
		return (1);
	}
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		i++;
		tmp = get_next_line(fd);
	}
	free(tmp);
	close(fd);
	return (i);
}

bool	is_whilespace(char	*c)
{
	if (*c == ' ' | *c == '\t')
		return (true);
	return (false);
}

void handle_no(t_cube3d *data, char	*line)
{
	int i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->NO = ft_strdup(line + 2);
	while (data->NO[i] != '\n')
		i++;
	data->NO[i] = '\0';
}

void handle_so(t_cube3d *data, char	*line)
{
	int i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->SO = ft_strdup(line + 2);
	while (data->SO[i] != '\n')
		i++;
	data->SO[i] = '\0';
}

void handle_we(t_cube3d *data, char	*line)
{
	int i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->WE = ft_strdup(line + 2);
	while (data->WE[i] != '\n')
		i++;
	data->WE[i] = '\0';
}

void handle_ea(t_cube3d *data, char	*line)
{
	int i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->EA = ft_strdup(line + 2);
	while (data->EA[i] != '\n')
		i++;
	data->EA[i] = '\0';
}
void	run_error_func(char	*buff, int fd, void(*func)(void*), void	*data)
{
	free(buff);
	buff = NULL;
	close(fd);
	func(data);
}

void	handle_color(t_cube3d	*data, char *buff)
{
	int	i;
	int i2;
	// char	*tmp;
	i = 1;
	i2 = 0;
	//3 loops for the 3 ints (or recursion)
	if (buff[0] == 'F')
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_floor(i, data, buff, 0);
	}
	else if (buff[0] == 'C')
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_celling(i, data, buff, 0);
	}
	(void)buff;
	(void)data;
}

bool	valid_nb(int	number)
{
	if (number >= 0 && number <= 255)
		return (true);
	return (false);
}

void	get_rgb_floor(int	start, t_cube3d	*data, char	*buff, int loop)
{
	int	i2;
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
		// printf("i2 is %i\n", i2);
		tmp = ft_substr(buff, start, i2);
		// printf("tmp is %s\n", tmp);
		data->f_color[loop] = ft_atoi(tmp);
		free(tmp);
		// printf("color is %i\n", data->f_color[loop]);
		if (!valid_nb(data->f_color[loop]))
		{
			printf("%i is invalid RGB\n", data->f_color[loop]);
			data->input_error = true;
			return ;
		}
	if (loop != 2 && !data->input_error)
		get_rgb_floor(start + i2, data, buff, ++loop);
}

void	invalid_rgb(char	*str, t_cube3d	*data, int loop)
{
	int	start;
	int test;
	start = 0;
	str++;

	while (is_whilespace(str) && str)
		str++;
	if (ft_strlen(str) > 12 && loop == 0)
	{
		data->input_error = true;
		printf("rgb string is too long\n");
		return ;
	}
	while (start < 3 && ft_isdigit(str[start]))
		start++;
	char	*tmp;
	tmp = ft_substr(str, 0, start);
	test = ft_atoi(tmp);
	free(tmp);
	if (test < 0 || test > 255)
		data->input_error = true;
	else if (loop < 3 && !data->input_error)
	{
		printf("recursion\n");
		loop++;
		invalid_rgb(str + (start + 1), data, loop);
	}
}

void	get_rgb_celling(int	start, t_cube3d	*data, char	*buff, int loop)
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
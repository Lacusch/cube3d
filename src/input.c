
#include "../includes/cube3d.h"

void	check_buffer(char	*line, t_cube3d	*data);
bool	meta_full(t_cube3d	*data);
int		ft_line(char *map);
bool	is_whilespace(char	*c);
void	handle_no(t_cube3d *data, char	*line);

void	input_data(t_cube3d	*data, char	*map)
{
	int		fd;
	char	*buff;

	int i = 0;
	buff = NULL;
	fd = open(map, O_RDWR);
	buff = get_next_line(fd);
	//get_data
	while (buff && !data->input_error && !meta_full(data))
	{
		check_buffer(buff, data);
		free(buff);
		buff = NULL;
		buff = get_next_line(fd);
		i++;
	}
	if (!meta_full(data))
	{
		free(buff);
		close(fd);
		missing_meta(data);
		return ;
	}
	if (invalid_meta(data))
	{
		//write a function that takes a functuib
		free(buff);
		close(fd);
		return ;
	}
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
	data_printf(data);
	free(buff);
	// free(tmp);
	close (fd);
	(void)data;
}

void	check_buffer(char	*line, t_cube3d	*data)
{

	if (line[0] == 'N' && line[1] == 'O')
		handle_no(data, line);
	else if (line[0] == 'S' && line[1] == 'O')
		data->SO = ft_strdup(line + 3);
	else if (line[0] == 'W' && line[1] == 'E')
		data->WE = ft_strdup(line + 3);
	else if (line[0] == 'E' && line[1] == 'A')
		data->EA = ft_strdup(line + 3);
	else if (line[0] == 'F')
		data->F_color = ft_strdup(line + 2);
	else if (line[0] == 'C')
		data->C_color = ft_strdup(line + 2);
	(void)line;
	(void)data;
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
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->NO = ft_strdup(line + 2);
	data->NO[ft_strlen(data->NO) + 1] = '\0';
}

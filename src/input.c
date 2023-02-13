
#include "../includes/cube3d.h"

void	check_buffer(char	*line, t_cube3d	*data);
bool	meta_full(t_cube3d	*data);
int		ft_line(char *map);

void	input_data(t_cube3d	*data, char	*map)
{
	int		fd;
	char	*buff;

	int i = 0;
	buff = NULL;
	fd = open(map, O_RDWR);
	buff = get_next_line(fd);
	check_buffer(buff, data);
	//get_data
	while (buff && !data->input_error && !meta_full(data))
	{
		check_buffer(buff, data);
		free(buff);
		buff = get_next_line(fd);
		i++;
	}
	//get_map
	char	*tmp;
	tmp = ft_strdup("");
	
	while (buff && !data->input_error)
	{
		buff = ft_strjoin(buff, ft_strdup("9"));
		tmp = ft_strjoin(tmp, buff);
		check_buffer(buff, data);
		free(buff);
		buff = get_next_line(fd);
	}
	printf("map line is %d\n", ft_line(map) - i);
	data->map = ft_split(tmp, '9');
	data_printf(data);
	free(buff);
	close (fd);
	(void)data;
}

void	check_buffer(char	*line, t_cube3d	*data)
{
	if (line[0] == 'N' && line[1] == 'O')
		data->NO = ft_strdup(line + 3);
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

#include"../includes/cube3d.h"

bool	is_whilespace(char	*c)
{
	if (*c == ' ' | *c == '\t')
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

bool	valid_nb(int number)
{
	if (number >= 0 && number <= 255)
		return (true);
	return (false);
}

void	terminate_str(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	str[i] = '\0';
}

bool	meta_full(t_cube3d	*data)
{
	if (data->NO && data->SO && data->WE && data->EA \
		&& data->F_color && data->C_color)
		return (true);
	return (false);
}

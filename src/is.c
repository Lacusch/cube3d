
#include "../includes/cube3d.h"

bool	is_closed(char	**map, t_map *map_data)
{
	int	line;

	line = 0;
	if (ft_strchr((map[line]), '0') != NULL)
	{
		write(STDERR_FILENO, NOT_CLOSED, 25);
		return (false);
	}
	while (line < map_data->height)
	{
		if (map[line][0] == '0' || map[line][map_data->width] == '0')
		{
			write(STDERR_FILENO, NOT_CLOSED, 25);
			return (false);
		}
		line++;
	}
	line--;
	if (ft_strchr((map[line]), '0') != NULL)
	{
		write(STDERR_FILENO, NOT_CLOSED, 25);
		return (false);
	}
	return (true);
}
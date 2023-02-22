
#include "../includes/cube3d.h"

void	fill(char **map, t_map *dimensions, int x, int y)
{
	if (y < 0 || y >= dimensions->height || x < 0 || x >= dimensions->width)
		return ;
	if (map[y][x] != '0' && map[y][x] != 'C'
	&& map[y][x] != 'P' && map[y][x] != 'E')
		return ;
	map[y][x] = 'F';
	fill(map, dimensions, x + 1, y);
	fill(map, dimensions, x - 1, y);
	fill(map, dimensions, x, y + 1);
	fill(map, dimensions, x, y - 1);
}

bool	flood_fill(char **map, t_map *dimentions, int player_x, int player_y)
{
	fill(map, dimentions, player_x, player_y);
	// if (ft_completable_test(data, dimentions->height) == true)
	// {
	// 	ft_free_char_array(data);
	// 	free(data);
	// 	return (true);
	// }
	printf("filled map is \n");
	matrix_printf(map);
	matrix_free(map);

	return (false);
}
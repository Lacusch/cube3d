
#include "../includes/cube3d.h"

void	fill4(char **map, t_map *dimensions, int x, int y)
{
	if (y < 0 || y >= dimensions->height || x < 0 || x >= dimensions->width)
		return ;
	if (map[y][x] != '0' && map[y][x] != 'N'
	&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W')
		return ;
	map[y][x] = 'F';
	fill4(map, dimensions, x + 1, y);
	fill4(map, dimensions, x - 1, y);
	fill4(map, dimensions, x, y + 1);
	fill4(map, dimensions, x, y - 1);
}

void	fill8(char **map, t_map *dimensions, int x, int y)
{
	if (y < 0 || y >= dimensions->height || x < 0 || x >= dimensions->width)
		return ;
	if (map[y][x] != '0' && map[y][x] != 'N'
	&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W')
		return ;
	map[y][x] = 'F';
	fill8(map, dimensions, x + 1, y);
	fill8(map, dimensions, x - 1, y);
	fill8(map, dimensions, x, y + 1);
	fill8(map, dimensions, x, y - 1);
	fill8(map, dimensions, x + 1, y + 1);
	fill8(map, dimensions, x -1 , y - 1);
}
void	flood_fill(char **map, t_cube3d *data, int player_x, int player_y)
{
	t_map	*dimentions;

	dimentions = malloc(sizeof(dimentions));
	(*dimentions).height = data->map_data.height;
	(*dimentions).width = data->map_data.width;
	fill8(map, dimentions, player_x, player_y);
	// printf("filled map is \n");
	free(dimentions);
	matrix_printf(map);
}



#include "../includes/cube3d.h"

// void	fill(char **tab, t_map *map, int x, int y)
// {
// 	if (y < 0 || y >= map->height || x < 0 || x >= map->width)
// 		return ;
// 	if (tab[y][x] != '0' && tab[y][x] != 'C'
// 	&& tab[y][x] != 'P' && tab[y][x] != 'E')
// 		return ;
// 	tab[y][x] = 'F';
// 	fill(tab, map, x + 1, y);
// 	fill(tab, map, x - 1, y);
// 	fill(tab, map, x, y + 1);
// 	fill(tab, map, x, y - 1);
// }

// bool	flood_fill(char **data, t_map *map, int player_x, int player_y)
// {
// 	fill(data, map, player_x, player_y);
// 	if (ft_completable_test(data, map->height) == true)
// 	{
// 		ft_free_char_array(data);
// 		free(data);
// 		return (true);
// 	}
// 	ft_free_char_array(data);
// 	free (data);
// 	return (false);
// }
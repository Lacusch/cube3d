#include "../includes/cube3d.h"

extern int g_map_size_x;
extern int g_map_size_y;
extern int g_width;
extern int g_height;

char	safe_map_read(char **map, int x, int y)
{
	if (x > g_map_size_y || y > g_map_size_x)
		return ('1');
	// printf("map[%i][%i]: %c\n", x, y, map[x][y]);
	return (map[x][y]);
}

int		safe_get_pixel(mlx_texture_t *texture, int pixel)
{
	int max_allowed;

	max_allowed = texture->width * texture->height * 4;
	if (pixel > max_allowed)
		return 0;
	return (texture->pixels[pixel]);
}

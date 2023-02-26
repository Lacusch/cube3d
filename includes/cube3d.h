
#ifndef CUBE3D_H
# define CUBE3D_H

// Includes

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI /2
#define DEGREE PI / 180

// Declarations

typedef struct s_cube3d
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F_color;
	char	*C_color;
}	t_cube3d;

bool	check_arg(int ac, char **av);
void	init_data(t_cube3d	*data);
void	matrix_free(char **matrix);
void	data_free(t_cube3d	*data);

int		is_same_str(char *str1, char *str2);
/** rgba_utils */
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);
int		get_rgba(int r, int g, int b, int a);
/** draw_utils */
void    ft_pixel_put(mlx_image_t *img, int x, int y, int color);
void	ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
/** draw_2d */
void	draw_background(mlx_t *mlx, mlx_image_t* img, char **map);
/** key_handler */
void	hook(void* param);
/** cube_utils.c */
int		map_cube_size(mlx_t *mlx);
/** calculation_utils */
void 	reset_360(float *val);
float 	hyp_dist(float ax, float ay, float bx, float by);
/** muck_map */
char	**muck_map(void);
/** safe_check */
char    safe_map_read(char **map, int x, int y);
int		safe_get_pixel(mlx_texture_t *texture, int pixel);
/** main */
void	draw(mlx_t	*mlx);

#endif
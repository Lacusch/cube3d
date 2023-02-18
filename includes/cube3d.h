
#ifndef CUBE3D_H
# define CUBE3D_H

// Includes

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"

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
void    ft_pixel_put(mlx_image_t *img, int x, int y, int color);
void	ft_draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, int color);
int		is_same_str(char *str1, char *str2);

#endif
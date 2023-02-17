
#ifndef CUBE3D_H
# define CUBE3D_H

//Includes

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>

#include "../lib/MLX42/include/MLX42/MLX42.h"
#include "../lib/libft/libft.h"
#include "errors.h"
//Declarations

typedef struct s_cube3d
{
	char	**map;
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*F_color;
	char	*C_color;
	char	start;
	bool	input_error;
	int		f_color[3];
	int		c_color[3];
}	t_cube3d;

void	data_printf(t_cube3d *data);
void	matrix_printf(char **matrix);

bool	check_arg(int ac, char **av);

void	init_data(t_cube3d	*data);

void	matrix_free(char **matrix);
void	data_free(t_cube3d	*data);
void	str_free(char	*str);

void	input_data(t_cube3d	*data, char	*map);
void	missing_meta(void	*data);
bool	invalid_meta(t_cube3d	*data);
bool	check_extension(char	*av1, char	*extension);

#endif

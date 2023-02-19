
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

bool	is_whilespace(char	*c);
int		ft_line(char *map);
bool	valid_nb(int	number);
void	terminate_str(char	*str);
bool	meta_full(t_cube3d	*data);

void	handle_no(t_cube3d *data, char	*line);
void	handle_so(t_cube3d *data, char	*line);
void	handle_we(t_cube3d *data, char	*line);
void	handle_ea(t_cube3d *data, char	*line);
void	handle_color(t_cube3d	*data, char *buff);

void	get_rgb_celling(int	start, t_cube3d	*data, char	*buff, int loop);
void	get_rgb_floor(int	start, t_cube3d	*data, char	*buff, int loop);
void	run_error_func(char	*buff, int fd, void(*func)(void*), void	*data);

void	input_data(t_cube3d	*data, char	*map);
void	check_buffer(char	*line, t_cube3d	*data);
void	get_rgb_floor(int	start, t_cube3d	*data, char	*buff, int loop);
void	get_rgb_celling(int	start, t_cube3d	*data, char	*buff, int loop);
bool	could_be_valid(char	*str);
bool	color_fine(int	color[3]);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 10:37:11 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/10 19:28:36 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "errors.h"
# include "constants.h"

typedef struct s_map
{
	int		height;
	int		width;
}	t_map;

typedef struct s_player
{
	int		x;
	int		y;
}	t_player;

typedef struct s_line
{
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}	t_line;

typedef struct s_cube3d
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			start;
	bool			input_error;
	int				f_color[3];
	int				c_color[3];
	int				view_mode;
	int				map_size_x;
	int				map_size_y;
	int				cube_size_x;
	int				cube_size_y;
	int				s_width;
	int				s_height;
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			pa;
	t_map			map_data;
	t_player		player;
	mlx_image_t		*img;
	mlx_texture_t	*texture_we;
	mlx_texture_t	*texture_ea;
	mlx_texture_t	*texture_so;
	mlx_texture_t	*texture_no;
	mlx_texture_t	*texture_tmp;
	mlx_t			*mlx;
}	t_cube3d;

typedef struct s_ray
{
	int		r;
	int		shade;
	int		mx;
	int		my;
	int		dof_h;
	int		dof_v;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	ang_tan;
	float	inv_tan;
	float	dis_t;
	float	line_h;
	float	line_offset;
	double	dis_h;
	float	hx;
	float	hy;
	double	dis_v;
	float	vx;
	float	vy;
	float	ca;
	float	tx;
}	t_ray;

bool	check_arg(int ac, char **av);
void	data_printf(t_cube3d *data);
void	matrix_printf(char **matrix);
bool	check_arg(int ac, char **av);
void	init_data(t_cube3d	*data);
void	matrix_free(char **matrix);
int		data_free(t_cube3d	*data, int status);
void	str_free(char	**str);
void	input_data(t_cube3d	*data, char	*map);
void	missing_meta(void	*data);
bool	invalid_meta(t_cube3d	*data);
bool	check_extension(char	*av1, char	*extension);
bool	is_whilespace(char	*c);
int		ft_line(char *map);
bool	valid_nb(int number);
void	terminate_str(char *str);
bool	meta_full(t_cube3d *data);
void	handle_no(t_cube3d *data, char	*line);
void	handle_so(t_cube3d *data, char	*line);
void	handle_we(t_cube3d *data, char	*line);
void	handle_ea(t_cube3d *data, char	*line);
void	handle_color(t_cube3d	*data, char *buff);
void	get_rgb_celling(int start, t_cube3d	*data, char	*buff, int loop);
void	get_rgb_floor(int start, t_cube3d	*data, char	*buff, int loop);
void	run_error_func(char	*buff, int fd, void (*func)(void*), void	*data);
void	input_data(t_cube3d	*data, char	*map);
void	check_buffer(char	*line, t_cube3d	*data);
void	get_rgb_floor(int start, t_cube3d	*data, char *buff, int loop);
void	get_rgb_celling(int start, t_cube3d	*data, char *buff, int loop);
void	could_be_valid(char	*str, t_cube3d	*data);
bool	color_fine(int color[3]);
bool	invalid_error(void);
void	invalid_rgb(t_cube3d	*data);
void	get_map(t_cube3d	*data, char	*buff, int fd);
bool	check_texture_extention(t_cube3d	*data);
bool	check_can_open(t_cube3d	*data);
bool	open_error(char	*file);
bool	invalid_error(void);
void	get_map(t_cube3d	*data, char	*buff, int fd);
void	invalid_error2(t_cube3d	*data);
void	set_error(t_cube3d	*data);
void	digit_check(t_cube3d	*data, int loop, int start, char	*str);
void	double_no(t_cube3d	*data);
void	double_so(t_cube3d	*data);
void	double_we(t_cube3d	*data);
void	double_ea(t_cube3d	*data);
void	double_color(t_cube3d	*data, char	*line);
void	check_map(t_cube3d	*data);
bool	invalid_line(char	*str, t_cube3d	*data);
bool	invalid_char_map(void);
bool	duplicate_player(void);
void	no_player(t_cube3d	*data);
void	map_valid_chars(t_cube3d	*data);
char	**matrix_dub(char	**matrix);
int		matrix_size(char	**matrix);
void	test_map(t_cube3d	*data);
int		get_max_width(char	**map);
bool	is_rectange(char	**map, int max_width);
void	make_recktange(char	**map, int max_width);
void	fill_string(char	**str_add, int max_width);
void	player_position(t_cube3d *data);
bool	is_closed(char	**map, t_map *map_data);
void	player_position_sub(t_cube3d *data, int line);
void	fill4(char **map, t_map *dimensions, int x, int y);
void	fill8(char **map, t_cube3d *data, int x, int y);
void	flood_fill(char **map, t_cube3d *data, int player_x, int player_y);
void	invalid_map(void);
int		is_same_str(char *str1, char *str2);
int		cast_int(float num);
int		get_r(int rgba);
int		get_g(int rgba);
int		get_b(int rgba);
int		get_a(int rgba);
int		get_rgba(int r, int g, int b, int a);
void	ft_pixel_put(mlx_image_t *img, int x, int y, int color);
void	ft_draw_line(mlx_image_t *img, t_line line, int color);
void	draw_background(t_cube3d *data);
void	hook(void *param);
char	keyh_read_map(t_cube3d *data, float x, float y);
float	modify_pos_angle(t_cube3d *data);
int		map_cube_size(t_cube3d *data);
void	reset_360(float *val);
double	hyp_dist(float a_x, float a_y, float b_x, float b_y);
char	safe_map_read(t_cube3d *data, int x, int y);
int		safe_get_pixel(mlx_texture_t *texture, int pixel);
void	draw_3d(t_cube3d *data);
void	init_rays(t_cube3d *data, t_ray *ray);
void	init_ray(t_cube3d *data, t_ray *ray);
void	set_ray_h_up(t_cube3d *data, t_ray *ray);
void	set_ray_h_down(t_cube3d *data, t_ray *ray);
void	set_ray_v_left(t_cube3d *data, t_ray *ray);
void	set_ray_v_right(t_cube3d *data, t_ray *ray);
void	find_horizontal_hit(t_cube3d *data, t_ray *ray);
void	find_vertical_hit(t_cube3d *data, t_ray *ray);
void	cast_horizontal(t_cube3d *data, t_ray *ray);
void	cast_vertical(t_cube3d *data, t_ray *ray);
void	wall_hit(t_cube3d *data, t_ray *ray);
void	draw_ceiling(t_cube3d *data, t_ray *ray);
void	draw_floor(t_cube3d *data, t_ray *ray);
void	cast_texture_to_screen(t_cube3d *data, t_ray *ray);
void	init_position(t_cube3d *data);
void	draw_rays_3d(t_cube3d *data);
t_line	new_line(int x0, int y0, int x1, int y1);
int		init_mlx(t_cube3d *data);
int		init_textures(t_cube3d *data);
void	free_close(int c, char *s1, char *s2);
void	el(void);
bool	can_open(char	*map);
bool	is_valid_nb_quete(char	*buff);
bool	is_valid_place_quete(char	*buff);
bool	double_coma(void);
bool	has_zero(char		**matrix);
t_map	get_space(char	**matrix);
bool	has_zero(char		**matrix);
t_map	get_space(char	**matrix);
bool	check_position(t_player	*player, t_map *map);

#endif
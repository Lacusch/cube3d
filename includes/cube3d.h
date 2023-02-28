
#ifndef CUBE3D_H
# define CUBE3D_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <math.h>

# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/libft.h"
# include "errors.h"

#define PI 3.1415926535
#define P2 PI / 2
#define P3 3 * PI /2
#define DEGREE PI / 180

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
	int 			map_size_y;
	int 			cube_size_x;
	int				cube_size_y;
	int				screen_width;
	int				screen_height;
	float			px;
	float			py;
	float			pdx;
	float 			pdy;
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
	int 	iter;
	int		shade;
	int		mx;
	int		my;
	int 	dof_h;
	int		dof_v;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	aTan;
	float	nTan;
	float	distT;
	float	lineH;
	float	lineO;
	double	disH;
	float 	disT;
	float	hx;
	float 	hy;
	double 	disV;
	float 	vx;
	float 	vy;
	float	ca;
	float 	tx;
}	t_ray;

bool	check_arg(int ac, char **av);
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
void	free_close(char	*buff, int fd);
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
void	player_position_sub(t_cube3d *data, int line);

void	fill4(char **map, t_map *dimensions, int x, int y);
void	fill8(char **map, t_cube3d *data, int x, int y);
void	flood_fill(char **map, t_cube3d *data, int player_x, int player_y);
bool	is_map_invalid(t_cube3d	*data, char	**matrix);
void	invalid_map(void);

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
void	draw_background(t_cube3d *data);
/** key_handler */
void	hook(void* param);
/** cube_utils.c */
int 	map_cube_size(t_cube3d *data);
/** calculation_utils */
void 	reset_360(float *val);
double 	hyp_dist(float ax, float ay, float bx, float by);
/** safe_check */
char	safe_map_read(t_cube3d *data, int x, int y);
int		safe_get_pixel(mlx_texture_t *texture, int pixel);
/** draw_3d */
void	draw_3d(t_cube3d *data);
/** main */
void 	draw_rays_3d(t_cube3d *data);

#endif
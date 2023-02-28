// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../includes/cube3d.h"

static int ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	return (EXIT_FAILURE);
}

static void init_ray_config(t_cube3d *data, t_ray *ray)
{
	(*ray).r = 0;
	(*ray).iter = 0;
	(*ray).shade = 1;
	(*ray).ra = data->pa - DEGREE * 30;
	reset_360(&(*ray).ra);
}

static void init_ray(t_cube3d *data, t_ray *ray)
{
	(*ray).dof_h = 0;
	(*ray).dof_v = 0;
	(*ray).iter = 0;
	(*ray).aTan = -1 / tan((*ray).ra);
	(*ray).nTan = - tan((*ray).ra);
	(*ray).disH = 1000000;
	(*ray).disV = 1000000;
	(*ray).hx = data->px;
	(*ray).hy = data->py;
	(*ray).vx = data->px;
	(*ray).vy = data->py;
	(*ray).rx = 0;
	(*ray).ry = 0;
}

static void cast_horizontal(t_cube3d *data, t_ray *ray)
{
	if ((*ray).ra > PI)
	{
		(*ray).ry = (((int)(data->py / data->cube_size_y)) * data->cube_size_y) - 0.0001;
		(*ray).rx = (data->py - (*ray).ry) * (*ray).aTan + data->px;
		(*ray).yo = - data->cube_size_y;
		(*ray).xo = - ((*ray).yo * (*ray).aTan);
	}
	if ((*ray).ra < PI)
	{
		(*ray).ry = (((int)(data->py / data->cube_size_y)) * data->cube_size_y) + data->cube_size_y;
		(*ray).rx = (data->py - (*ray).ry) * (*ray).aTan + data->px;
		(*ray).yo = data->cube_size_y;
		(*ray).xo = - ((*ray).yo * (*ray).aTan);
	}
	if ((*ray).ra == 0 || (*ray).ra == PI)
	{
		(*ray).rx = data->px;
		(*ray).ry = data->py;
		(*ray).dof_h = data->map_size_x;
	}
	while ((*ray).dof_h < data->map_size_x)
	{
		(*ray).mx = (int)((*ray).rx / data->cube_size_x);
		(*ray).my = (int)((*ray).ry / data->cube_size_y);
		if (((*ray).mx >= 0 && (*ray).mx < data->map_size_x) && ((*ray).my >= 0 && (*ray).my < data->map_size_y) && ((safe_map_read(data, (*ray).my, (*ray).mx) == '1')))
		{
			(*ray).hx = (*ray).rx;
			(*ray).hy = (*ray).ry;
			(*ray).disH = hyp_dist(data->px, data->py, (*ray).hx, (*ray).hy);
			(*ray).dof_h = data->map_size_x;
		}
		else
		{
			(*ray).rx += (*ray).xo;
			(*ray).ry += (*ray).yo;
			(*ray).dof_h += 1;
		}
	}
}

static void cast_vertical(t_cube3d *data, t_ray *ray)
{
	if ((*ray).ra > P2 && (*ray).ra < P3)
	{
		(*ray).rx = (((int)(data->px / data->cube_size_x)) * data->cube_size_x) - 0.0001;
		(*ray).ry = (data->px - (*ray).rx) * (*ray).nTan + data->py;
		(*ray).xo = - data->cube_size_x;
		(*ray).yo = - ((*ray).xo * (*ray).nTan);
	}
	if ((*ray).ra < P2 || (*ray).ra > P3)
	{
		(*ray).rx = (((int)(data->px / data->cube_size_x)) * data->cube_size_x) + data->cube_size_x; 
		(*ray).ry = (data->px - (*ray).rx) * (*ray).nTan + data->py;
		(*ray).xo = data->cube_size_x;
		(*ray).yo = - ((*ray).xo * (*ray).nTan);
	}
	if ((*ray).ra == 0 || (*ray).ra == PI)
	{
		(*ray).rx = data->px;
		(*ray).ry = data->py;
		(*ray).dof_v = data->map_size_y;
	}
	while ((*ray).dof_v < data->map_size_x)
	{
		(*ray).mx = (int)((*ray).rx / data->cube_size_x);
		(*ray).my = (int)((*ray).ry / data->cube_size_y);
		if (((*ray).mx >= 0 && (*ray).mx < data->map_size_x) && ((*ray).my >= 0 && (*ray).my < data->map_size_y) && ((safe_map_read(data, (*ray).my, (*ray).mx) == '1')))
		{
			(*ray).vx = (*ray).rx;
			(*ray).vy = (*ray).ry;
			(*ray).disV = hyp_dist(data->px, data->py, (*ray).vx, (*ray).vy);
			(*ray).dof_v = data->map_size_x;
		}
		else
		{
			(*ray).rx += (*ray).xo;
			(*ray).ry += (*ray).yo;
			(*ray).dof_v += 1;
		}
	}
}

static void wall_hit(t_cube3d *data, t_ray *ray)
{
	// vertical wall hit
	if ((*ray).disV < (*ray).disH)
	{
		if ((*ray).ra > P2 && (*ray).ra < P3)
			data->texture_tmp = data->texture_we;
		else
			data->texture_tmp = data->texture_ea;
		(*ray).rx = (*ray).vx;
		(*ray).ry = (*ray).vy;
		(*ray).disT = (*ray).disV;
		(*ray).shade = 0;
	}
	// horizontal wall hit
	if ((*ray).disH < (*ray).disV)
	{
		if ((*ray).ra >= 0 && (*ray).ra <= PI)
			data->texture_tmp = data->texture_so;
		else
			data->texture_tmp = data->texture_no;
		(*ray).rx = (*ray).hx;
		(*ray).ry = (*ray).hy;
		(*ray).disT = (*ray).disH;
		(*ray).shade = 1;
	}
}

static void ft_draw_3d_line(t_cube3d *data, t_ray *ray)
{
	// ----------------------------
	// draw 3d
	// FIX FISHEYE
	(*ray).ca = data->pa - (*ray).ra;
	reset_360(&((*ray).ca));
	(*ray).disT = (*ray).disT * cos((*ray).ca);
	// End fish eye
	(*ray).lineH = (data->cube_size_y * data->mlx->height * 0.66) / (*ray).disT;
	(*ray).lineO = data->mlx->height * 0.35 - (*ray).lineH / 2;
	(*ray).tx = 0;
	// -- Ray iterations
	int iter_len = data->mlx->width / data->mlx->width;
	// DRAW VERTICAL LINESs
	while ((*ray).iter < iter_len)
	{
		ft_draw_line(data->img, ((*ray).r * iter_len) + (*ray).iter, 0, ((*ray).r * iter_len) + (*ray).iter, (*ray).lineO, get_rgba(data->c_color[0], data->c_color[1], data->c_color[2], 255)); // ceiling
		ft_draw_line(data->img, ((*ray).r * iter_len) + (*ray).iter, data->mlx->width, ((*ray).r * iter_len) + (*ray).iter, (*ray).lineO + (*ray).lineH, get_rgba(data->f_color[0], data->f_color[1], data->f_color[2], 255)); // floor
		// Mapping to texture
		int y = 0;
		float ty_step = data->texture_tmp->height / (*ray).lineH;
		float ty = ty_step;
		if ((*ray).shade == 1)
			(*ray).tx = (int)((data->texture_tmp->width * (*ray).rx) / data->cube_size_x) % data->texture_tmp->width;
		else
			(*ray).tx = (int)((data->texture_tmp->height * (*ray).ry) / data->cube_size_y) % data->texture_tmp->height;
		while (y < (*ray).lineH)
		{
			int BPP;
			BPP = sizeof(int32_t);
			int rc = safe_get_pixel(data->texture_tmp, (BPP * (((int)ty) * data->texture_tmp->height) + ((int)(*ray).tx * BPP)) + 0);
			int gc = safe_get_pixel(data->texture_tmp, (BPP * (((int)ty) * data->texture_tmp->height) + ((int)(*ray).tx * BPP)) + 1);
			int bc = safe_get_pixel(data->texture_tmp, (BPP * (((int)ty) * data->texture_tmp->height) + ((int)(*ray).tx * BPP)) + 2);
			int ac = safe_get_pixel(data->texture_tmp, (BPP * (((int)ty) * data->texture_tmp->height) + ((int)(*ray).tx * BPP)) + 3);
			ft_pixel_put(data->img, ((*ray).r * iter_len) + (*ray).iter, (*ray).lineO + y, get_rgba(rc, gc, bc, ac));
			ty += ty_step;
			y++;
		}
		(*ray).iter++;
	}
}

void draw_rays_3d(t_cube3d *data)
{
	t_ray	ray;

	init_ray_config(data, &ray);
	while (ray.r < data->mlx->width)
	{
		init_ray(data, &ray);
		cast_horizontal(data, &ray);
		cast_vertical(data, &ray);
		wall_hit(data, &ray);
		if (data->view_mode == 1)
			ft_draw_line(data->img, data->px, data->py, ray.rx, ray.ry, 0x00FF00FF);
		else
			ft_draw_3d_line(data, &ray);
		ray.ra += (DEGREE / (data->mlx->width / 60));
		reset_360(&ray.ra);
		ray.r++;
	}
}

int32_t	main(int ac, char** av)
{
	t_cube3d	data;
	
	init_data(&data);
	if (check_arg(ac, av))
		return (EXIT_FAILURE);
	input_data(&data, av[1]);
	if (data.input_error)
	{
		data_free(&data);
		return (EXIT_FAILURE);
	}
	data_printf(&data);
	data.map_size_x = data.map_data.width;
	data.map_size_y = data.map_data.height;
	if (!(data.mlx = mlx_init(data.screen_width, data.screen_height, "CUB3D", true)))
    		return (ft_error());
    data.img = mlx_new_image(data.mlx, data.screen_width, data.screen_height);
    if (!data.img)
    	perror("Error creating img");
    map_cube_size(&data);
    // if (data.start == 'N')
    // 	g_pa = -P2 - DEGREE;
	// else if (data.start == 'S')
	// 	g_pa = P2 - DEGREE;
	// else if (data.start == 'E')
	// 	g_pa = 0 + DEGREE;
	// else if (data.start == 'W')
	// 	g_pa = PI - DEGREE;
    data.px = data.player.x * data.cube_size_x;
    data.py = data.player.y * data.cube_size_y;
    data.pdx = cos(data.pa);
    data.pdy = sin(data.pa);
   	data.texture_we = mlx_load_png(data.we);
   	data.texture_ea = mlx_load_png(data.ea);
   	data.texture_so = mlx_load_png(data.so);
   	data.texture_no = mlx_load_png(data.no);
    draw_3d(&data);
    mlx_loop_hook(data.mlx, &hook, &data);
    mlx_loop(data.mlx);
    mlx_terminate(data.mlx);
	data_free(&data);
	// system("leaks cub3D");
	return (EXIT_SUCCESS);
}

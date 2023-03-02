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
	data.map_size_x = data.map_data.width;
	data.map_size_y = data.map_data.height;
	if (!(data.mlx = mlx_init(data.s_width, data.s_height, "CUB3D", true)))
    		return (ft_error());
    data.img = mlx_new_image(data.mlx, data.s_width, data.s_height);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:13:11 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/10 15:38:33 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int32_t	main(int ac, char **av)
{
	t_cube3d	data;

	init_data(&data);
	if (check_arg(ac, av))
	{
		system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	input_data(&data, av[1]);
	if (data.input_error)
	{
		system("leaks cub3D");
		data_free(&data, EXIT_FAILURE);
		return (1);
	}
	if (init_textures(&data) == EXIT_FAILURE)
	{
		system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	if (init_mlx(&data) == EXIT_FAILURE)
	{
		system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	map_cube_size(&data);
	init_position(&data);
	draw_3d(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	data_free(&data, EXIT_SUCCESS);
	system("leaks cub3D");
	return (EXIT_SUCCESS);
}

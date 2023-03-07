/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:13:11 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/07 12:05:27 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int32_t	main(int ac, char **av)
{
	t_cube3d	data;

	init_data(&data);
	if (check_arg(ac, av))
		return (EXIT_FAILURE);
	input_data(&data, av[1]);
	if (data.input_error)
		return (data_free(&data, EXIT_FAILURE));
	if (init_textures(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_mlx(&data) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	map_cube_size(&data);
	init_position(&data);
	draw_3d(&data);
	mlx_loop_hook(data.mlx, &hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
	data_free(&data, EXIT_SUCCESS);
	return (0);
}

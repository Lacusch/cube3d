/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 08:01:18 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/07 12:03:43 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	init_mlx(t_cube3d *data)
{
	data->map_size_x = data->map_data.width;
	data->map_size_y = data->map_data.height;
	data->mlx = mlx_init(data->s_width, data->s_height, "CUB3D", 1);
	if (!data->mlx)
	{
		write(STDERR_FILENO, MLX_ERROR, 32);
		return (data_free(data, EXIT_FAILURE));
	}
	data->img = mlx_new_image(data->mlx, data->s_width, data->s_height);
	if (!data->img)
	{
		mlx_terminate(data->mlx);
		write(STDERR_FILENO, MLX_IMG_ERROR, 34);
		return (data_free(data, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

int	init_textures(t_cube3d *data)
{
	if (data->we)
		data->texture_we = mlx_load_png(data->we);
	if (data->ea)
		data->texture_ea = mlx_load_png(data->ea);
	if (data->so)
		data->texture_so = mlx_load_png(data->so);
	if (data->no)
		data->texture_no = mlx_load_png(data->no);
	if (!data->texture_we
		|| !data->texture_ea
		|| !data->texture_so
		|| !data->texture_no)
	{
		write(STDERR_FILENO, MLX_TEXTURE, 32);
		return (data_free(data, EXIT_FAILURE));
	}
	return (EXIT_SUCCESS);
}

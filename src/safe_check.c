/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 10:25:00 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 14:33:02 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

char	safe_map_read(t_cube3d *data, int x, int y)
{
	if (x > data->map_size_y || y >= data->map_size_x)
		return ('1');
	return (data->map[x][y]);
}

int	safe_get_pixel(mlx_texture_t *texture, int pixel)
{
	int	max_allowed;

	max_allowed = texture->width * texture->height * 4;
	if (pixel >= max_allowed)
		return (0);
	return (texture->pixels[pixel]);
}

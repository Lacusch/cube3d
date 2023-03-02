/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:34 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 13:29:35 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	double_no(t_cube3d	*data)
{
	write(STDERR_FILENO, DO_NO_ERROR, 40);
	data->input_error = true;
}

void	double_so(t_cube3d	*data)
{
	write(STDERR_FILENO, DO_SO_ERROR, 40);
	data->input_error = true;
}

void	double_we(t_cube3d	*data)
{
	write(STDERR_FILENO, DO_WE_ERROR, 39);
	data->input_error = true;
}

void	double_ea(t_cube3d	*data)
{
	write(STDERR_FILENO, DO_EA_ERROR, 39);
	data->input_error = true;
}

void	double_color(t_cube3d	*data, char	*line)
{
	if (line[0] == 'F' && (data->f_color[0] != -1 || \
		data->f_color[1] != -1 || data->f_color[1] != -1))
	{
		write(STDERR_FILENO, DO_F_ERROR, 29);
		data->input_error = true;
	}
	else if (line[0] == 'C' && (data->c_color[0] != -1 \
		|| data->c_color[1] != -1 || data->c_color[1] != -1))
	{
		write(STDERR_FILENO, DO_C_ERROR, 31);
		data->input_error = true;
	}
}

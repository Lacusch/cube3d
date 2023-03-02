/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:12 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 13:30:13 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	matrix_free(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		free(matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	free(matrix);
	matrix = NULL;
}

void	data_free(t_cube3d	*data)
{
	if (data->map != NULL)
		matrix_free(data->map);
	if (data->no != NULL)
		str_free(data->no);
	if (data->so != NULL)
		str_free(data->so);
	if (data->we != NULL)
		str_free(data->we);
	if (data->ea != NULL)
		str_free(data->ea);
}

void	str_free(char	*str)
{
	free(str);
	str = NULL;
}

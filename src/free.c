/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:30:12 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/03 11:15:47 by segarcia         ###   ########.fr       */
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

int	data_free(t_cube3d	*data, int status)
{
	if (data->map != NULL && data->map)
		matrix_free(data->map);
	if (data->no != NULL && data->no)
		str_free(&data->no);
	if (data->so != NULL && data->so)
		str_free(&data->so);
	if (data->we != NULL && data->we)
		str_free(&data->we);
	if (data->ea != NULL && data->ea)
		str_free(&data->ea);
	return (status);
}

void	str_free(char	**str)
{
	if (*str != NULL)
	{
		free(*str);
		*str = NULL;
	}
}

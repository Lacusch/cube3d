/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:08 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 13:29:10 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	data_printf(t_cube3d *data)
{
	printf("NO is %s\n", data->no);
	printf("SO is %s\n", data->so);
	printf("WE is %s\n", data->we);
	printf("EA is %s\n", data->ea);
	printf("Floor color is %i %i %i\n", data->f_color[0], \
		data->f_color[1], data->f_color[2]);
	printf("Celling color is %i %i %i\n", data->c_color[0], \
		data->c_color[1], data->c_color[2]);
	printf("\n");
	printf("map height is %i ", data->map_data.height);
	printf(", witdth is %i\n", data->map_data.width);
	printf("player position is:\nx:%i, y:%i\n", data->player.x, data->player.y);
	printf("player direction is %c\n", data->start);
	printf("Map is: \n");
	matrix_printf(data->map);
	printf("\n");
}

void	matrix_printf(char **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i] != NULL)
	{
		printf("%s\n", matrix[i]);
		i++;
	}
}

char	**matrix_dub(char	**matrix)
{
	int		i;
	char	**env;

	i = 0;
	if (matrix == NULL || matrix[i] == NULL)
		return (NULL);
	env = malloc(sizeof(char *) * (matrix_size(matrix) + 1));
	if (env == NULL)
		return (NULL);
	while (matrix[i] != NULL)
	{
		env[i] = ft_strdup(matrix[i]);
		i++;
	}
	env[i] = NULL;
	return (env);
}

int	matrix_size(char	**matrix)
{
	int	i;

	i = 0;
	while (matrix[i] != NULL)
		i++;
	return (i);
}

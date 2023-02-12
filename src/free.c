
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
	if (data->NO != NULL)
		free(data->NO);
	if (data->SO != NULL)
		free(data->NO);
	if (data->WE != NULL)
		free(data->NO);
	if (data->EA != NULL)
		free(data->NO);
	if (data->F_color != NULL)
		free(data->NO);
	if (data->C_color != NULL)
		free(data->NO);
	init_data(data);
}

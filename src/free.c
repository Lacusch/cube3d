
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
		str_free(data->NO);
	if (data->SO != NULL)
		str_free(data->SO);
	if (data->WE != NULL)
		str_free(data->WE);
	if (data->EA != NULL)
		str_free(data->EA);
}

void	str_free(char	*str)
{
	free(str);
	str = NULL;
}

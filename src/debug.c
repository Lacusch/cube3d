
#include "../includes/cube3d.h"

void	data_printf(t_cube3d *data)
{
	data->NO[ft_strlen(data->NO +1)] = '\0';
	data->SO[ft_strlen(data->SO +1)] = '\0';
	data->WE[ft_strlen(data->WE +1)] = '\0';
	data->EA[ft_strlen(data->EA +1)] = '\0';
	printf("NO is %s\n", data->NO);
	printf("SO is %s\n", data->SO);
	printf("WE is %s\n", data->WE);	
	printf("EA is %s\n", data->EA);	
	printf("Floor is: %s\n", data->F_color);	
	printf("Ceiling is: %s\n", data->C_color);	
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
		printf("%s", matrix[i]);
		matrix[i] = NULL;
		i++;
	}
	matrix = NULL;
}

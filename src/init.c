
#include "../includes/cube3d.h"

void	init_data(t_cube3d	*data)
{
	data->map = NULL;
	data->NO = NULL;
	data->SO = NULL;
	data->WE = NULL;
	data->EA = NULL;
	data->F_color = NULL;
	data->C_color = NULL;
	data->input_error = false;
	data->start = '\0';
}

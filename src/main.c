// -----------------------------------------------------------------------------
// Codam Coding College, Amsterdam @ 2022-2023 by W2Wizard.
// See README in the root project for more information.
// -----------------------------------------------------------------------------

#include "../includes/cube3d.h"

int32_t	main(int ac, char **av)
{
	t_cube3d		data;

	init_data(&data);
	if (check_arg(ac, av))
	{
		system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	input_data(&data, av[1]);
	if (data.input_error)
	{
		data_free(&data);
		system("leaks cub3D");
		return (EXIT_FAILURE);
	}
	data_free(&data);
	system("leaks cub3D");
	return (EXIT_SUCCESS);
}


#include "../includes/cube3d.h"

bool	input_data(t_cube3d	*data, char	*map)
{
	int	fd;
	char	*buff;

	buff = NULL;
	fd = open(map, O_RDWR);
	printf("map is:\n%s\n", map);
	printf("fd is %i\n", fd);
	buff = get_next_line(fd);
	printf("%s\n", buff);
	while (buff)
	{
		printf("%s\n", buff);
		free(buff);
		buff = get_next_line(fd);
	}
	free(buff);
	close (fd);
	(void)data;
	return (true);
}

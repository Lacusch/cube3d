#include "../includes/cube3d.h"

void	get_map(t_cube3d	*data, char	*buff, int fd)
{
	char	*tmp;
	char	*tmp2;

	if (!data->input_error)
	{
		printf("get_map here\n");
		check_buffer(buff, data);
		tmp = ft_strdup("");
		while (buff && !data->input_error)
		{
			tmp2 = tmp;
			tmp = ft_strjoin(tmp2, buff);
			free(tmp2);
			free(buff);
			buff = get_next_line(fd);
		}
		data->map = ft_split(tmp, '\n');
		free(tmp);
		free(buff);
		close(fd);
	}
	check_map(data);
	if (!data->input_error)
		data_printf(data);
}

void	check_map(t_cube3d	*data)
{
	(void)data;
}

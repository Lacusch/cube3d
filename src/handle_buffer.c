
#include "../includes/cube3d.h"

void	handle_no(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->NO = ft_strdup(line + 2);
	while (data->NO[i] != '\n')
		i++;
	data->NO[i] = '\0';
}

void	handle_so(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->SO = ft_strdup(line + 2);
	while (data->SO[i] != '\n')
		i++;
	data->SO[i] = '\0';
}

void	handle_we(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->WE = ft_strdup(line + 2);
	while (data->WE[i] != '\n')
		i++;
	data->WE[i] = '\0';
}

void	handle_ea(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->EA = ft_strdup(line + 2);
	while (data->EA[i] != '\n')
		i++;
	data->EA[i] = '\0';
}

void	handle_color(t_cube3d	*data, char *buff)
{
	int	i;
	int	i2;

	i = 1;
	i2 = 0;
	if (buff[0] == 'F')
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_floor(i, data, buff, 0);
	}
	else if (buff[0] == 'C')
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_celling(i, data, buff, 0);
	}
}

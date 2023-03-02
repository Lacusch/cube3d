#include "../includes/cube3d.h"

void	handle_no(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	if (data->no != NULL)
		return (double_no(data));
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->no = ft_strdup(line + 2);
	while (data->no[i] != '\n')
		i++;
	data->no[i] = '\0';
}

void	handle_so(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	if (data->so != NULL)
		return (double_so(data));
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->so = ft_strdup(line + 2);
	while (data->so[i] != '\n')
		i++;
	data->so[i] = '\0';
}

void	handle_we(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	if (data->we != NULL)
		return (double_we(data));
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->we = ft_strdup(line + 2);
	while (data->we[i] != '\n')
		i++;
	data->we[i] = '\0';
}

void	handle_ea(t_cube3d *data, char	*line)
{
	int	i;

	i = 0;
	if (data->ea != NULL)
		return (double_ea(data));
	while (is_whilespace(line + 2) == true && line)
		line++;
	if (*line == '\0')
	{
		data->input_error = true;
		return ;
	}
	data->ea = ft_strdup(line + 2);
	while (data->ea[i] != '\n')
		i++;
	data->ea[i] = '\0';
}

void	handle_color(t_cube3d	*data, char *buff)
{
	int	i;
	int	i2;

	i = 1;
	i2 = 0;
	(void)i2;
	double_color(data, buff);
	if (buff[0] == 'F' && data->input_error != true)
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_floor(i, data, buff, 0);
	}
	else if (buff[0] == 'C' && data->input_error != true)
	{
		while (is_whilespace(&buff[i]) == true && buff[i])
			i++;
		get_rgb_celling(i, data, buff, 0);
	}
}

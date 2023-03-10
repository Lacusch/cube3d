/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:31:18 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/10 13:21:47 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	input_data(t_cube3d	*data, char	*map)
{
	int		fd;
	char	*buff;

	buff = NULL;
	fd = open(map, O_RDWR);
	buff = get_next_line(fd);
	while (buff && !data->input_error && !meta_full(data))
	{
		check_buffer(buff, data);
		if (buff != NULL)
			str_free(&buff);
		if (data->input_error)
			return ;
		buff = get_next_line(fd);
	}
	if (!meta_full(data) && data->input_error == false)
		run_error_func(buff, fd, missing_meta, (void *)data);
	else if (invalid_meta(data) && data->input_error == false)
		free_close(fd, buff, NULL);
	if (data->input_error)
		return (str_free(&buff));
	else if (!data->input_error)
		get_map(data, buff, fd);
}

void	check_buffer(char	*line, t_cube3d	*data)
{
	if (line == NULL)
		return ;
	if (line[0] == 'N' && line[1] == 'O')
		handle_no(data, line);
	else if (line[0] == 'S' && line[1] == 'O')
		handle_so(data, line);
	else if (line[0] == 'W' && line[1] == 'E')
		handle_we(data, line);
	else if (line[0] == 'E' && line[1] == 'A')
		handle_ea(data, line);
	else if (line[0] == 'F' || line[0] == 'C')
	{
		could_be_valid(line, data);
		if (data->input_error == true)
			return ;
		handle_color(data, line);
	}
}

void	get_rgb_floor(int start, t_cube3d	*data, char *buff, int loop)
{
	int		i2;
	char	*tmp;

	tmp = NULL;
	i2 = 0;
	if (loop == 0 && *buff == ',')
		return (invalid_rgb(data));
	if (loop != 0)
		buff++;
	while (i2 < 3 && ft_isdigit(buff[start + i2]) && buff)
		i2++;
	tmp = ft_substr(buff, start, i2);
	data->f_color[loop] = ft_atoi(tmp);
	free(tmp);
	if (!valid_nb(data->f_color[loop]))
		return (invalid_rgb(data));
	if (loop != 2 && !data->input_error)
		get_rgb_floor(start + i2, data, buff, ++loop);
}

void	get_rgb_celling(int start, t_cube3d *data, char *buff, int loop)
{
	int		i2;
	char	*tmp;

	tmp = NULL;
	i2 = 0;
	if (loop == 0 && *buff == ',')
		return (invalid_rgb(data));
	if (loop != 0)
		buff++;
	while (i2 < 3 && ft_isdigit(buff[start + i2]) && buff)
			i2++;
	tmp = ft_substr(buff, start, i2);
	data->c_color[loop] = ft_atoi(tmp);
	free(tmp);
	if (!valid_nb(data->c_color[loop]))
	{
		invalid_rgb(data);
		return ;
	}
	if (loop != 2 && !data->input_error)
		get_rgb_celling(start + i2, data, buff, ++loop);
}

void	free_close(int c, char *s1, char *s2)
{
	if (c >= 0)
		close(c);
	if (s1 != NULL)
		free(s1);
	if (s2 != NULL)
		free(s2);
}

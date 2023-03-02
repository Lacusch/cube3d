/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:38 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/02 13:29:39 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

bool	invalid_line(char	*str, t_cube3d	*data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'W' || str[i] == 'E')
		{
			if (data->start != '\0')
				return (duplicate_player());
			data->start = str[i];
		}
		else if (str[i] != '1' && str[i] != '0' && str[i] != ' ')
			return (invalid_char_map());
		i++;
	}
	return (false);
}

bool	invalid_char_map(void)
{
	write(STDERR_FILENO, WRONG_CHAR_MAP, 32);
	return (true);
}

bool	duplicate_player(void)
{
	write(STDERR_FILENO, TO_MANY_PLAYER, 24);
	return (true);
}

void	no_player(t_cube3d	*data)
{
	write(STDERR_FILENO, NO_PLAYER, 17);
	data->input_error = true;
}

void	invalid_map(void)
{
	write(STDERR_FILENO, INVALID_MAP, 19);
}

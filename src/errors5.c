/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:29:43 by slaszlo-          #+#    #+#             */
/*   Updated: 2023/03/03 13:11:32 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	el(void)
{
	write(STDERR_FILENO, EMPTY_LINE, 33);
}

bool	can_open(char	*map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write (STDERR_FILENO, NO_MAP, 27);
		return (false);
	}
	close (fd);
	return (true);
}

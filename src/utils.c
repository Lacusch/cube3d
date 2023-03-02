/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slaszlo- <slaszlo-@student.42heibronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:35:54 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 13:17:52 by slaszlo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	is_same_str(char *str1, char *str2)
{
	int	i;

	if (!str1 || !str2)
		return (0);
	if (!ft_strlen(str1) || !ft_strlen(str2))
		return (0);
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int	cast_int(float num)
{
	return ((int)(num));
}

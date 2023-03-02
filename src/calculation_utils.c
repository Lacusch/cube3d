/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 02:14:23 by segarcia          #+#    #+#             */
/*   Updated: 2023/03/02 03:31:43 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	reset_360(float *val)
{
	if (*val < 0)
		*val += (2 * PI);
	if (*val > (2 * PI))
		*val -= (2 * PI);
	return ;
}

double	hyp_dist(float a_x, float a_y, float b_x, float b_y)
{
	float	a;
	float	b;

	a = (b_x - a_x) * (b_x - a_x);
	b = (b_y - a_y) * (b_y - a_y);
	return (sqrt(a + b));
}

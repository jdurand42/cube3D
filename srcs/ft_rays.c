/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/17 15:20:33 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 	ft_setup(t_data *data, int **map)
{
	int 	i;
	double 	angle;

	i = 0;
	if (!(data->vectors = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	angle = ft_get_angle(data, map);
	while (i < W)
	{
		(data->vectors[i])->a[0] = data->posx;
		(data->vectors[i])->a[1] = data->posy;
		(data->vectors[i])->b[0] = data->posx + 100 * cos((angle + 60) / 2) - i - 60 / data->R[0];
		(data->vectors[i])->b[1] = data->posy + 100 * sin(ft_toradian((angle + 60) / 2)) - i - 60 / data->R[1];
		i++; // ???
	}
}

int 	ft_get_angle(t_data *data, int **map)
{
	doube angle;

	if (map[(int)posy][(int)posx] + '0' == 'N')
		angle = 0;
	else if (map[(int)posy][(int)posx] + '0' == 'E')
		angle = 90;
	else if (map[(int)posy][(int)posx] + '0' == 'S')
	 	angle = 180;
	else if (map[(int)posy][(int)posx] + '0' == 'W')
		angle = 180 + 90;
	map[(int)posy][(int)posx] = 0;
	return (angle);
}

angle 	ft_toradian(double angle)
{
	return (pi / 180 * angle);
}

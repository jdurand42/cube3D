/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/18 19:17:56 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setup_rays(t_data *data, int **map)
{
	int 	i;

	i = 0;
	if (!(data->vectors = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	data->angle = ft_get_angle(data, map);
	printf("ANGLE: %lf\n", data->angle);
	while (i < data->R[0])
	{
		data->vectors[i].x0 = data->posx;
		data->vectors[i].y0 = data->posy;
		data->vectors[i].x1 = data->posx + (1 * (cos(ft_toradian(data->angle + (60 / 2) - (i * (60 / data->R[0]))))));
		data->vectors[i].y1 = data->posy + (1 * (sin(ft_toradian(data->angle + (60 / 2) - (i * (60 / data->R[0]))))));
		i++;
	}
}

void 	do_rays(t_data *data)
{
	int i = 0;

	while (i < data->R[0])
	{
		data->vectors[i].x0 = data->posx;
		data->vectors[i].y0 = data->posy;
		data->vectors[i].x1 = data->posx + (1 * (cos(ft_toradian(data->angle + (60 / 2) - (i * (60 / data->R[0]))))));
		data->vectors[i].y1 = data->posy + (1 * (sin(ft_toradian(data->angle + (60 / 2) - (i * (60 / data->R[0]))))));
		i++;
		if (i == data->R[0] / 2)
			printf("ray %d: x1, y1: %lf, %lf\n", i, data->vectors[i].x1, data->vectors[i].y1);
	}
}

int 	ft_get_angle(t_data *data, int **map)
{
	double angle;

	if (map[(int)data->posy][(int)data->posx] + '0' == 'N')
		angle = 90;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'E')
		angle = 0;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'S')
	 	angle = 270;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'W')
		angle = 180;
	map[(int)data->posy][(int)data->posx] = 0;
	return (angle);
}

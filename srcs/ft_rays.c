/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/18 15:39:31 by jdurand          ###   ########.fr       */
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
		i++;
	}
}

int 	ft_get_angle(t_data *data, int **map)
{
	double angle;

	if (map[(int)data->posy][(int)data->posx] + '0' == 'N')
		angle = 0;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'E')
		angle = 90;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'S')
	 	angle = 180;
	else if (map[(int)data->posy][(int)data->posx] + '0' == 'W')
		angle = 180 + 90;
	map[(int)data->posy][(int)data->posx] = 0;
	return (angle);
}

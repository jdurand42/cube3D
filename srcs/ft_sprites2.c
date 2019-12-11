/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 17:00:22 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 18:53:31 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_zbuffer(t_data *data, t_sprite *sprite, float pas)
{
	float angle_s;
	int size;
	int	pixel;

	pixel = -1;
	size = 0;
	angle_s = sprite->angle_f;
	while (size <= sprite->sizex)
	{
		pixel = ft_raying_sprite(data, angle_s);
		if (pixel != -1)
			break;
		size++;
		angle_s += pas;
	}
	ft_draw_sprites(data, pixel, sprite->sizex - size, sprite);
}

int 		ft_raying_sprite(t_data *data, float angle_s)
{
	int i;

	i = 0;
	while (i < data->R[0] - 1)
	{
		if (angle_s >= data->vec[i].angle && angle_s <= data->vec[i + 1].angle)
			return (i);
		i++;
	}
	return (-1);
}

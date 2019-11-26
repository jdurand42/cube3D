/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:45:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/26 14:56:14 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_keyboard_loop(t_data *data, int keycode)
{
	if (keycode == 13)
	{
		if (!data->map[(int)(data->posy - (sin(ft_toradian(data->angle)) * speed * 0.001))][(int)data->posx])
			data->posy -= (sin(ft_toradian(data->angle)) * speed * 0.001);
		if (!data->map[(int)data->posy][(int)(data->posx += (cos(ft_toradian(data->angle)) * speed * 0.001))])
			data->posx += (cos(ft_toradian(data->angle)) * speed * 0.001);
	}
	else if (keycode == 1)
	{
		data->posy += (sin(ft_toradian(data->angle)) * speed * 0.001);
		data->posx -= (cos(ft_toradian(data->angle)) * speed * 0.001);
	}
	else if (keycode == 0)
	{
		data->angle += speed_angle;
	}
	else if (keycode == 2)
	{
		data->angle -= speed_angle;
	}
	else if (keycode == 15)
		data->angle += 90;
	if (data->angle > 360)
		data->angle = 0;
	else if (data->angle < 0)
		data->angle = 360;
}

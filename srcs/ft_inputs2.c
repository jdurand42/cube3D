/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:23:30 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:15:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_collision(t_data *data, float angle)
{
	float	ad_x;
	float	ad_y;

	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * SPEED * SPEED_DIV;
	ad_y = data->cam.roty * SPEED * SPEED_DIV;
	if (!ft_collision2(data, ad_x, ad_y))
		ft_advance(data, angle, 1);
}

int		ft_collision2(t_data *data, float ad_x, float ad_y)
{
	if (data->cam.roty > 0)
	{
		if (data->map[(int)(data->posy - ad_y - RAYON)]
		[(int)(data->posx + ad_x)] > 0)
			return (1);
	}
	else
	{
		if (data->map[(int)(data->posy - ad_y + RAYON)]
		[(int)(data->posx + ad_x)] > 0)
			return (1);
	}
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy - ad_y)]
		[(int)(data->posx + ad_x + RAYON)] > 0)
			return (1);
	}
	else
	{
		if (data->map[(int)(data->posy - ad_y)]
		[(int)(data->posx + ad_x - RAYON)] > 0)
			return (1);
	}
	return (0);
}

void	ft_collision_back(t_data *data, float angle)
{
	float	ad_x;
	float	ad_y;

	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * SPEED * SPEED_DIV;
	ad_y = data->cam.roty * SPEED * SPEED_DIV;
	if (!ft_collision_back2(data, ad_x, ad_y))
		ft_advance(data, angle, 2);
}

int		ft_collision_back2(t_data *data, float ad_x, float ad_y)
{
	if (data->cam.roty > 0)
	{
		if (data->map[(int)(data->posy + ad_y + RAYON)]
		[(int)(data->posx - ad_x)] > 0)
			return (1);
	}
	else
	{
		if (data->map[(int)(data->posy + ad_y - RAYON)]
		[(int)(data->posx - ad_x)] > 0)
			return (1);
	}
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy + ad_y)]
		[(int)(data->posx - ad_x - RAYON)] > 0)
			return (1);
	}
	else
	{
		if (data->map[(int)(data->posy + ad_y)]
		[(int)(data->posx - ad_x + RAYON)] > 0)
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:23:30 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 16:25:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_collision(t_data *data, float angle)
{
	int		hity;
	int		hitx;
	float	ad_x;
	float	ad_y;

	hitx = 0;
	hity = 0;
	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * SPEED * SPEED_DIV;
	ad_y = data->cam.roty * SPEED * SPEED_DIV;
	if (data->cam.roty > 0) // up
	{
		if (data->map[(int)(data->posy - ad_y - RAYON)][(int)(data->posx + ad_x)] > 0) // hit
			hity = 1;
	}
	else
		if (data->map[(int)(data->posy - ad_y + RAYON)][(int)(data->posx + ad_x)] > 0)
			hity = 1;
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy - ad_y)][(int)(data->posx + ad_x + RAYON)] > 0)
			hitx = 1;
	}
	else
	{
		if (data->map[(int)(data->posy - ad_y)][(int)(data->posx + ad_x - RAYON)] > 0)
			hitx = 1;
	}
	if (hity < 1 || hitx < 1)
		ft_advance(data, angle, 1);
}

void 	ft_collision_back(t_data *data, float angle)
{
	int		hity;
	int		hitx;
	float	ad_x;
	float	ad_y;

	hitx = 0;
	hity = 0;
	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * SPEED * SPEED_DIV;
	ad_y = data->cam.roty * SPEED * SPEED_DIV;
	if (data->cam.roty > 0) // up
	{
		if (data->map[(int)(data->posy + ad_y + RAYON)][(int)(data->posx - ad_x)] > 0) // hit
			hity = 1;
	}
	else
		if (data->map[(int)(data->posy + ad_y - RAYON)][(int)(data->posx - ad_x)] > 0)
			hity = 1;
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy + ad_y)][(int)(data->posx - ad_x - RAYON)] > 0)
			hitx = 1;
	}
	else
	{
		if (data->map[(int)(data->posy + ad_y)][(int)(data->posx - ad_x + RAYON)] > 0)
			hitx = 1;
	}
	if (hity < 1 || hitx < 1)
		ft_advance(data, angle, 2);
}

void 	ft_strafe(t_data *data, int id)
{
	float	strafe_angle;

	strafe_angle = data->cam.angle + (90 * id);
	if (strafe_angle > 359)
		strafe_angle = strafe_angle - 360;
	else if (strafe_angle < 0)
		strafe_angle = 360 + strafe_angle;
	ft_collision(data, strafe_angle);
}

void 	ft_advance(t_data *data, float angle, int param)
{
	if (param == 1)
	{
		data->posy -= (sin(ft_toradian(angle)) * SPEED * SPEED_DIV);
		data->posx += (cos(ft_toradian(angle)) * SPEED * SPEED_DIV);
	}
	else if (param == 2)
	{
		data->posy += (sin(ft_toradian(angle)) * SPEED * SPEED_DIV);
		data->posx -= (cos(ft_toradian(angle)) * SPEED * SPEED_DIV);
	}
}

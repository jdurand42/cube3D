/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:45:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/26 19:15:28 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_keyboard_loop(t_data *data, int keycode)
{
	printf("angle: %lf\n", data->cam.angle);
	printf("x, y: %lf, %lf\n", data->posx, data->posy);
	if (keycode == 13)
	{
		ft_do_colision(data, 1);
//		data->posy -= (sin(ft_toradian(data->cam.angle)) * speed * speed_div);
//		data->posx += (cos(ft_toradian(data->cam.angle)) * speed * speed_div);
	}
	else if (keycode == 1)
	{
		data->posy += (sin(ft_toradian(data->cam.angle)) * speed * 0.001);
		data->posx -= (cos(ft_toradian(data->cam.angle)) * speed * 0.001);
	}
	else if (keycode == 0)
	{
		data->cam.angle += speed_angle;
	}
	else if (keycode == 2)
	{
		data->cam.angle -= speed_angle;
	}
	else if (keycode == 15)
		data->cam.angle += 90;
	if (data->cam.angle > 359)
		data->cam.angle = 0;
	else if (data->cam.angle < 0)
		data->cam.angle = 359;
}

void	ft_do_colision(t_data *data, int choice) // pas encore bon
{
	float	x_go;
	float	y_go;

	data->cam.rotx = cos(ft_toradian(data->cam.angle));
	data->cam.roty = sin(ft_toradian(data->cam.angle));

	x_go = data->posx + data->cam.rotx * speed * speed_div;
	y_go = data->posy - data->cam.roty * speed * speed_div;
	//printf("x_go, y_go: %f, %lf\n", x_go, y_go);
	if (data->cam.rotx > 0) // to the right, x++ check at correct value;
	{
		if (data->map[(int)y_go][(int)(x_go)] != 0) // collision + rayon bug
			x_go += (int)x_go - x_go;
			//x_go -= rayon;
	}
	else
	{
		if (data->map[(int)y_go][(int)x_go] != 0)
			x_go -= ((int)x_go + 1) - x_go;
	}
	if (data->cam.roty > 0)
	{
		if (data->map[(int)y_go][(int)x_go] != 0)
			y_go -= (int)y_go + 1 - y_go;
	}
	else
	{
		if (data->map[(int)(y_go)][(int)x_go] != 0)
			y_go += (int)y_go - y_go;
	}
	data->posx = x_go;
	data->posy = y_go;
	//printf("x_go, y_go: %f, %lf\n", x_go, y_go);
}

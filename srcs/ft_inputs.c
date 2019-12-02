/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:45:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/02 18:23:39 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

/*
** w = 13
** s = 1
** a = 0
** d = 2
** r = 15
** t = 17
** > = 124
** < = 123
** q = 12
** e = 14
** esc = 53
*/

int 	ft_keyboard_loop(t_data *data, int keycode)
{
//	printf("angle: %lf\n", data->cam.angle);
//	printf("x, y: %lf, %lf\n", data->posx, data->posy);
	printf("keycode: %d\n", keycode);
	printf("angle: %lf\n", data->cam.angle);
	if (keycode == 13)
		ft_collision(data, data->cam.angle);
	else if (keycode == 1)
		ft_collision_back(data, data->cam.angle);
	else if (keycode == 0)
		ft_strife(data, 1);
	else if (keycode == 2)
		ft_strife(data, -1);
	else if (keycode == 12)
		data->cam.angle += speed_angle;
	else if (keycode == 14)
		data->cam.angle -= speed_angle;
	else if (keycode == 15)
		data->cam.angle -= 90;
	else if (keycode == 17)
		data->cam.angle += 90;
	else if (keycode == 53)
		return (1);
	if (data->cam.angle > 359)
		data->cam.angle = 0;
	else if (data->cam.angle < 0)
		data->cam.angle = 359;
	return (0);
}

void 	ft_collision(t_data *data, float angle)
{
	int		hity = 0;
	int		hitx = 0;
	float	ad_x;
	float	ad_y;

	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * speed * speed_div;
	ad_y = data->cam.roty * speed * speed_div;
	if (data->cam.roty > 0) // up
	{
		if (data->map[(int)(data->posy - ad_y - rayon)][(int)(data->posx + ad_x)] > 0) // hit
			hity = 1;
	}
	else
		if (data->map[(int)(data->posy - ad_y + rayon)][(int)(data->posx + ad_x)] > 0)
			hity = 1;
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy - ad_y)][(int)(data->posx + ad_x + rayon)] > 0)
			hitx = 1;
	}
	else
	{
		if (data->map[(int)(data->posy - ad_y)][(int)(data->posx + ad_x - rayon)] > 0)
			hitx = 1;
	}
	if (hity < 1 || hitx < 1)
		ft_advance(data, angle, 1);
}

void 	ft_collision_back(t_data *data, float angle)
{
	int		hity = 0;
	int		hitx = 0;
	float	ad_x;
	float	ad_y;

	data->cam.roty = sin(ft_toradian(angle));
	data->cam.rotx = cos(ft_toradian(angle));
	ad_x = data->cam.rotx * speed * speed_div;
	ad_y = data->cam.roty * speed * speed_div;
	if (data->cam.roty > 0) // up
	{
		if (data->map[(int)(data->posy + ad_y + rayon)][(int)(data->posx - ad_x)] > 0) // hit
			hity = 1;
	}
	else
		if (data->map[(int)(data->posy + ad_y - rayon)][(int)(data->posx - ad_x)] > 0)
			hity = 1;
	if (data->cam.rotx > 0)
	{
		if (data->map[(int)(data->posy + ad_y)][(int)(data->posx - ad_x - rayon)] > 0)
			hitx = 1;
	}
	else
	{
		if (data->map[(int)(data->posy + ad_y)][(int)(data->posx - ad_x + rayon)] > 0)
			hitx = 1;
	}
	if (hity < 1 || hitx < 1)
		ft_advance(data, angle, 2);
}

void 	ft_strife(t_data *data, int id)
{
	float	strife_angle;

	strife_angle = data->cam.angle + (90 * id);
	if (strife_angle > 359)
		strife_angle = strife_angle - 360;
	else if (strife_angle < 0)
		strife_angle = 270 + data->cam.angle;
//	printf("%lf, %lf\n", data->cam.angle, strife_angle);
	ft_collision(data, strife_angle);
}

void 	ft_advance(t_data *data, float angle, int param)
{
	if (param == 1)
	{
		data->posy -= (sin(ft_toradian(angle)) * speed * speed_div);
		data->posx += (cos(ft_toradian(angle)) * speed * speed_div);
	}
	else if (param == 2)
	{
		data->posy += (sin(ft_toradian(angle)) * speed * speed_div);
		data->posx -= (cos(ft_toradian(angle)) * speed * speed_div);
	}
}
/*
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
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:45:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 17:57:57 by jdurand          ###   ########.fr       */
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

int		keypress(int keycode, void *param)
{
	t_data *data;

	data = (t_data*)param;
	if (keycode == 13)
		data->move |= UPWARD;
	if (keycode == 1)
		data->move |= BACKWARD;
	if (keycode == 0)
		data->move |= STRAFE_L;
	if (keycode == 2)
		data->move |= STRAFE_R;
	if (keycode == 12)
		data->move |= LEFT;
	if (keycode == 14)
		data->move |= RIGHT;
	if (keycode == 15)
		data->cam.angle -= 90;
	if (keycode == 17)
		data->cam.angle += 90;
	if (data->cam.angle > 359)
		data->cam.angle = 1;
	else if (data->cam.angle < 0)
		data->cam.angle = 359;
	ft_main_loop(data);
	return (1);
}

int 	keyrelease(int keycode, void *param)
{
	t_data *data;

	data = (t_data*)param;
	if (keycode == 13)
		data->move -= UPWARD;
	if (keycode == 1)
		data->move -= BACKWARD;
	if (keycode == 0)
		data->move -= STRAFE_L;
	if (keycode == 2)
		data->move -= STRAFE_R;
	if (keycode == 12)
		data->move -= LEFT;
	if (keycode == 14)
		data->move -= RIGHT;
	if (keycode == 53)
		ft_exit_all(data);
	return (1);
}

void    ft_do_looping(t_data *data)
{
	mlx_hook(data->mlx_wd, 2, 0, keypress, data);
	//mlx_hook(data->mlx_wd, 3, 0, release_key, data);
	//mlx_key_hook(data->mlx_wd, ft_main_loop, data);
	//printf("\n\nlooooop\n\n");
	mlx_loop(data->mlx_p);
}

int 	ft_keyboard_loop(t_data *data)
{
//	printf("angle: %lf\n", data->cam.angle);
//	printf("x, y: %lf, %lf\n", data->posx, data->posy);
	//printf("keycode: %d\n", keycode);
	printf("angle: %lf\n", data->cam.angle);
	if (data->move & 1)
		ft_collision(data, data->cam.angle);
	if (data->move & 2)
		ft_collision_back(data, data->cam.angle);
	if (data->move & 4)
		ft_strafe(data, 1);
	if (data->move & 8)
		ft_strafe(data, -1);
	if (data->move & 16)
		data->cam.angle += speed_angle;
	if (data->move & 32)
		data->cam.angle -= speed_angle;
	if (data->move & 64)
		ft_exit_all(data);
	if (data->cam.angle > 359)
		data->cam.angle = 1;
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

void 	ft_strafe(t_data *data, int id)
{
	float	strafe_angle;

	strafe_angle = data->cam.angle + (90 * id);
	if (strafe_angle > 359)
		strafe_angle = strafe_angle - 360;
	else if (strafe_angle < 0)
		strafe_angle = 360 + strafe_angle;
//	printf("%lf, %lf\n", data->cam.angle, strafe_angle);
	ft_collision(data, strafe_angle);
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

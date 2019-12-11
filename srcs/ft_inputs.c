/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inputs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:45:47 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 18:57:24 by jdurand          ###   ########.fr       */
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
	mlx_hook(data->mlx_wd, 3, 0, keyrelease, data);
	mlx_hook(data->mlx_wd, 17, 0, exit_program, data);
	mlx_hook(data->mlx_wd, 2, 0, ft_main_loop, data);
	mlx_loop(data->mlx_p);
}

int 	ft_keyboard_loop(t_data *data)
{
	int move;

	move = 0;
	if (data->move & 1)
		ft_collision(data, data->cam.angle);
	if (data->move & 2)
		ft_collision_back(data, data->cam.angle);
	if (data->move & 4)
		ft_strafe(data, 1);
	if (data->move & 8)
		ft_strafe(data, -1);
	if (data->move & 16)
		data->cam.angle += SPEED_ANGLE;
	if (data->move & 32)
		data->cam.angle -= SPEED_ANGLE;
	if (data->move & 64)
		ft_exit_all(data);
	if (data->cam.angle > 359)
		data->cam.angle = 1;
	else if (data->cam.angle < 0)
		data->cam.angle = 359;
	return (0);
}

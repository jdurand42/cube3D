/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/11/19 17:19:09 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

/*
** w = 13
** s = 1
** a = 0
** d = 2
** r = 15
** esc = 53
*/

void 	ft_setbackground(t_data *data)
{
	int i = 0; int j = 0;

	while (j < data->R[1])
	{
		while (i < (data->R[0] * 4))
		{
			if (j < data->R[1] / 2)
			{
				data->img[i + (j * data->size_line)] = (char)50;
				data->img[i + 1 + (j * data->size_line)] = (char)50;
				data->img[i + 2 + (j * data->size_line)] = (char)50;
				data->img[i + 3 + (j * data->size_line)] = (char)0;
				i += 4;
			}
			else
			{
				data->img[i + (j * data->size_line)] = (char)0;
				data->img[i + 1 + (j * data->size_line)] = (char)0;
				data->img[i + 2 + (j * data->size_line)] = (char)0;
				data->img[i + 3 + (j * data->size_line)] = (char)0;
				i += 4;
			}
		}
		i = 0;
		j += 1;
	}
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void 	ft_putcamera(t_data *data)
{

	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

int 	ft_keyboard_loop(int keycode, void *params)
{
	t_data *data;

	data = (t_data*)params;
	printf("keycode %d\n", keycode);
	if (keycode == 13 && data->posx > 0 && data->posy > 0 && data->posx < data->width && data->posy < data->height)
	{
		if (data->posx > 0 && data->posy > 0 && data->posx < data->width && data->posy < data->height)
		{
			data->posy -= (sin(ft_toradian(data->angle)) * speed * 0.001);
			data->posx += (cos(ft_toradian(data->angle)) * speed * 0.001);
		}
	}
	else if (keycode == 1 && data->posx > 0 && data->posy > 0 && data->posx < data->width && data->posy < data->height)
	{
		if (data->posx > 0 && data->posy > 0 && data->posx < data->width && data->posy < data->height)
		{
			data->posy += (sin(ft_toradian(data->angle)) * speed * 0.001);
			data->posx -= (cos(ft_toradian(data->angle)) * speed * 0.001);
		}
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
	printf("x, y: %lf, %lf\nangle: %lf\n", data->posx, data->posy, data->angle);
	int i = 0;
	ft_setbackground(data);
	do_rays(data);
	return (0);
}

int 	ft_game_loop(t_data *data, int **map)
{

	if (!ft_setup_mlx(data, map))
		return (0);
	ft_setup_rays(data, map);
	ft_setbackground(data);
	do_rays(data);
	mlx_key_hook(data->mlx_wd, ft_keyboard_loop, data);
	mlx_loop(data->mlx_p);
	return (1);
}

int 	ft_setup_mlx(t_data *data, int **map)
{
	data->map = map;
	if ((data->mlx_p = mlx_init()))
		printf("succes mlx\n");
	data->mlx_wd = mlx_new_window(data->mlx_p, data->R[0], data->R[1], "Wolf3D");
	if (data->mlx_wd)
		printf("%p\n", data->mlx_wd);
	data->mlx_img = mlx_new_image(data->mlx_p, data->R[0], data->R[1]);
	if (!data->mlx_img)
		return (0);
	data->img = mlx_get_data_addr(data->mlx_img, &(data->bit_p_p), &(data->size_line), &(data->endian));
	printf("bpp: %d, sizeline: %d, endian: %d\n", data->bit_p_p, data->size_line, data->endian);
	return (1);
}

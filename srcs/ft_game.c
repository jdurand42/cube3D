/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/07 12:22:57 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setbackground(t_data *data)
{
	int i = 0; int j = 0;

	while (j < data->R[1])
	{
		while (i < (data->R[0] * 4))
		{
			if (j < data->R[1] / 2)
			{
				data->img[i + (j * data->sl)] = data->F >> 16;
				data->img[i + 1 + (j * data->sl)] = data->F >> 8;
				data->img[i + 2 + (j * data->sl)] = data->F >> 0;
				data->img[i + 3 + (j * data->sl)] = (char)0;
				i += 4;
			}
			else
			{
				data->img[i + (j * data->sl)] = data->C >> 16;
				data->img[i + 1 + (j * data->sl)] = data->C >> 8;
				data->img[i + 2 + (j * data->sl)] = data->C >> 0;
				data->img[i + 3 + (j * data->sl)] = (char)0;
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

int	ft_main_loop(int keycode, void *params)
{
	t_data *data;

	data = (t_data*)params;
	printf("keycode %d\n", keycode);
	ft_keyboard_loop(data, keycode);
	ft_reset_tsprite(data->tsprite, data->s_max);
	if (data->exit_status == 1)
		exit(0);
//	printf("x, y: %lf, %lf post loop\n", data->posx, data->posy);
	int i = 0;
	ft_setbackground(data);
	do_rays(data);
//	ft_show_tsprite(data->tsprite, data->s_max);
//	printf("wallx %lf, wally %lf, dist: %lf, angle %lf\n", data->vec[data->R[0] / 2].id_wallx
//	, data->vec[data->R[0] / 2].id_wally, data->vec[data->R[0] / 2].dist_towall, data->vec[data->R[0] / 2].angle);
	//mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->tex[3].img_p, data->R[0] / 2, data->R[1] / 2);
	return (0);
}

int 	ft_game_loop(t_data *data, int **map)
{
	if (!ft_setup_mlx(data, map))
		return (0);
	ft_do_tsprite(data);
	ft_setup_rays(data, map);
	ft_setbackground(data);
	ft_show_tsprite(data->tsprite, data->s_max);
	do_rays(data);
	mlx_key_hook(data->mlx_wd, ft_main_loop, data);
	//printf("ddddddddd\n");
//	printf("%d\n", data->exit_status); // ?????
	mlx_loop(data->mlx_p);
	//printf("dasdadas");
	return (1);
}

int 	ft_setup_mlx(t_data *data, int **map)
{
	data->map = map;
	if (!(data->mlx_p = mlx_init()))
		return (0);
	if (!(data->mlx_wd = mlx_new_window(data->mlx_p, data->R[0], data->R[1], "Wolf3D")))
		return (0);
	data->mlx_img = mlx_new_image(data->mlx_p, data->R[0], data->R[1]);
	if (!data->mlx_img)
		return (0);
	data->img = mlx_get_data_addr(data->mlx_img, &(data->bpp), &(data->sl), &(data->endian));
	if (!(ft_setup_tex(data)))
		return (0);
	data->exit_status = 0;
	printf("bpp: %d, sizeline: %d, endian: %d\n", data->bpp, data->sl, data->endian);
	return (1);
}

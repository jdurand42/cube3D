/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 18:56:09 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setbackground(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < data->R[1])
	{
		while (i < (data->R[0] * 4))
		{
			if (j < data->R[1] / 2)
			{
				ft_coloriage(data, i, j, data->C);
				i += 4;
			}
			else
			{
				ft_coloriage(data, i , j, data->F);
				i += 4;
			}
		}
		i = 0;
		j += 1;
	}
}

void 	ft_coloriage(t_data *data, int i, int j, unsigned int color)
{
	data->img[i + (j * data->sl)] = color >> 0;
	data->img[i + 1 + (j * data->sl)] = color >> 8;
	data->img[i + 2 + (j * data->sl)] = color >> 16;
	data->img[i + 3 + (j * data->sl)] = (char)0;
}

int	ft_main_loop(int keycode, void *param)
{
	t_data *data;

	data = (t_data*)param;
	keypress(keycode, param);
	if (data->exit_status == 1)
		ft_exit_all(data);
	ft_keyboard_loop(data);
	ft_reset_tsprite(data->tsprite, data->s_max, data);
	ft_setbackground(data);
	do_rays(data);
	return (0);
}

int 	ft_game_loop(t_data *data, int **map)
{
	if (!ft_setup_mlx(data, map))
		return (0);
	data->move = 0;
	ft_do_tsprite(data);
	ft_setup_rays(data, map);
	ft_setbackground(data);
	do_rays(data);
	//export_as_bmp("./screens/screenshot.bmp", data->img, data->R[0], data->R[1]);
	ft_do_looping(data);
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
	return (1);
}

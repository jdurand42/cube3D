/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_game.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:26:07 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 17:09:46 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	ft_setbackground(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < data->r[1])
	{
		while (i < (data->r[0] * 4))
		{
			if (j < data->r[1] / 2)
			{
				ft_coloriage(data, i, j, data->c);
				i += 4;
			}
			else
			{
				ft_coloriage(data, i, j, data->f);
				i += 4;
			}
		}
		i = 0;
		j += 1;
	}
}

void	ft_coloriage(t_data *data, int i, int j, unsigned int color)
{
	data->img[i + (j * data->sl)] = color >> 0;
	data->img[i + 1 + (j * data->sl)] = color >> 8;
	data->img[i + 2 + (j * data->sl)] = color >> 16;
	data->img[i + 3 + (j * data->sl)] = (char)0;
}

int		ft_main_loop(int keycode, void *param)
{
	t_data	*data;

	data = (t_data*)param;
	keypress(keycode, param);
	if (data->exit_status == 1)
		ft_exit_all(data);
	ft_keyboard_loop(data);
	ft_setbackground(data);
	do_rays(data);
	return (0);
}

int		ft_game_loop(t_data *data, int **map)
{
	if (!ft_setup_mlx(data, map))
		return (0);
	data->move = 0;
	ft_do_tsprite(data);
	ft_setup_rays(data);
	ft_setbackground(data);
	do_rays(data);
	if (data->save == 1)
		export_as_bmp("./screens/screenshot.bmp", data->img, data->r[0],
		data->r[1]);
	ft_do_looping(data);
	return (1);
}

int		ft_setup_mlx(t_data *data, int **map)
{
	data->map = map;
	if (!(data->mlx_p = mlx_init()))
		return (0);
	if (!(data->mlx_wd = mlx_new_window(data->mlx_p, data->r[0], data->r[1],
		"Wolf3D")))
		return (0);
	data->mlx_img = mlx_new_image(data->mlx_p, data->r[0], data->r[1]);
	if (!data->mlx_img)
		return (0);
	data->img = mlx_get_data_addr(data->mlx_img, &(data->bpp), &(data->sl),
	&(data->endian));
	if (!(ft_setup_tex(data)))
		return (0);
	data->exit_status = 0;
	return (1);
}

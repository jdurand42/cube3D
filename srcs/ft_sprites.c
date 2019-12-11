/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:43:47 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	ft_do_dist_sprite(t_data *data)
{
	int		i;
	float	distx;
	float	disty;

	i = 0;
	while (i < data->s_max)
	{
		ft_init_dist_tsprite(data, &distx, &disty, i);
		if (distx > 0)
		{
			data->tsprite[i].angle = to_d(acos(ft_abs(data->tsprite[i].rotx)));
			if (disty > 0)
				data->tsprite[i].angle = 360 - data->tsprite[i].angle;
		}
		else
		{
			data->tsprite[i].angle = to_d(acos(ft_abs(data->tsprite[i].rotx)));
			if (disty < 0)
				data->tsprite[i].angle = 90 + (90 - data->tsprite[i].angle);
			else
				data->tsprite[i].angle = 180 + data->tsprite[i].angle;
		}
		i++;
	}
	ft_do_sort_sprite(data);
}

void	ft_init_dist_tsprite(t_data *data, float *distx, float *disty, int i)
{
	*distx = (data->tsprite[i].x + 0.5) - data->posx;
	*disty = (data->tsprite[i].y + 0.5) - data->posy;
	data->tsprite[i].dist = sqrt((*distx * *distx) + (*disty * *disty));
	data->tsprite[i].rotx = *distx / data->tsprite[i].dist;
	data->tsprite[i].roty = *disty / data->tsprite[i].dist;
}

void	ft_check_if_visible(t_data *data)
{
	int		i;
	float	pas;

	i = 0;
	pas = 60 / (float)data->R[0];
	while (i < data->s_max)
	{
		data->tsprite[i].sizey = (int)(data->R[1] / data->tsprite[i].dist);
		data->tsprite[i].sizex = data->tsprite[i].sizey * 1.33;
		data->tsprite[i].angle_f = data->tsprite[i].angle - (pas *
			(data->tsprite[i].sizex / 2));
		data->tsprite[i].angle_l = data->tsprite[i].angle + (pas *
			(data->tsprite[i].sizex / 2));
		data->tsprite[i].angle_f = lissage_angle(data->tsprite[i].angle_f);
		data->tsprite[i].angle_l = lissage_angle(data->tsprite[i].angle_l);
		ft_zbuffer(data, &data->tsprite[i], pas);
		i++;
	}
}

void	ft_do_tsprite(t_data *data)
{
	int	x;
	int	y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (!(data->tsprite = (t_sprite*)malloc(data->s_max * sizeof(t_sprite))))
		ft_exit_all(data);
	while (y < data->height)
	{
		while (x < data->width)
		{
			if (data->map[y][x] == 2)
			{
				data->tsprite[i].x = x;
				data->tsprite[i].y = y;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:15:57 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/09 15:24:33 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_do_sort_sprite(t_data *data)
{
	int i;

	i = 0;
	while (i < data->s_max - 1)
	{
		if (data->tsprite[i].dist < data->tsprite[i + 1].dist)
		{
			ft_swap_sprite(&data->tsprite[i], &data->tsprite[i + 1]);
			i = 0;
		}
		else
			i++;
	}
}

void 	ft_swap_sprite(t_sprite *a, t_sprite *b)
{
	float	f_b;
	double  lf_b;
	int		i_b;

	i_b = a->x;
	a->x = b->x;
	b->x = i_b;
	i_b = a->y;
	a->y = b->y;
	b->y = i_b;
	i_b = a->pixel_hit;
	a->pixel_hit = b->pixel_hit;
	b->pixel_hit = i_b;
	i_b = a->hit;
	a->hit = b->hit;
	b->hit = i_b;
	f_b = a->dist;
	a->dist = b->dist;
	b->dist = f_b;
	f_b = a->distx;
	a->distx = b->distx;
	b->distx = f_b;
	f_b = a->disty;
	a->disty = b->disty;
	b->disty = f_b;
	f_b = a->offset;
	a->offset = b->offset;
	b->offset = f_b;
	lf_b = a->rot;
	a->rot = b->rot;
	b->rot = lf_b;
	lf_b = a->angle;
	a->angle = b->angle;
	b->angle = lf_b;

}

double  ft_todegree(double radian)
{
	return (radian * (180 / pi));
}

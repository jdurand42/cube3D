/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:15:57 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 18:18:07 by jdurand          ###   ########.fr       */
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
	float  lf_b;
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
	lf_b = a->rotx;
	a->rotx = b->rotx;
	b->rotx = lf_b;
	lf_b = a->roty;
	a->roty = b->roty;
	b->roty = lf_b;
	lf_b = a->angle;
	a->angle = b->angle;
	b->angle = lf_b;
	i_b = a->sizex;
	a->sizex = b->sizex;
	b->sizex = i_b;
	i_b = a->sizey;
	a->sizey = b->sizey;
	b->sizey = i_b;

}

float  ft_todegree(float radian)
{
	return (radian * (180 / pi));
}

float	lissage_angle(float angle)
{
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 359)
		angle = angle - 359;
	if (angle < 0)
		angle = 360 + angle;
	else if (angle > 359)
		angle = angle - 359;
	return (angle);
}

int	ft_comp_sprite_angle(float angle_f, float angle_l, t_data *data)
{
	if (angle_f >= data->cam.angle - 30 && angle_f <= data->cam.angle + 30)
		return (1);
	if (angle_l >= data->cam.angle - 30 && angle_l <= data->cam.angle + 30)
		return (1);
	if (angle_f <= data->cam.angle - 30 && angle_f >= data->cam.angle + 30)
		return (1);
	if (angle_l <= data->cam.angle - 30 && angle_l >= data->cam.angle + 30)
		return (1);
	return (0);
}


void ft_lst_free(t_list **lst)
{
	t_list *b;
	t_list *b_n;

	b = *lst;
	if (b == NULL)
	{
		printf("b NULL\n");
		return ;
	}
	while (b != NULL)
	{
		b_n = b->next;
		free(b->content);
		b->content = NULL;
		free(b);
		b = NULL;
		b = b_n;
	}
}

void ft_clear_list(void *content)
{
	printf("now here\n");
	printf("%s\n", (char*)content);
	if (content)
		free(content);
	content = NULL;
}

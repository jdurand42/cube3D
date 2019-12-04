/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/04 18:05:42 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void ft_check_sprite(t_data *data, t_int *coor, int i, int map_value)
{
	t_lst_sprite		*b;
	int					xsign;
	int					ysign;

	if (map_value != 2)
		return ;
	if (data->vec[i].rotx > 0)
		xsign = 0;
	else
		xsign = -1;
	if (data->vec[i].roty > 0)
		ysign = -1;
	else
		ysign = 0;
	// if champ de vision ?
	b = data->sprite_lst;
	while (b)
	{
		if ((int)coor->x + xsign == b->x && (int)coor->y + ysign == b->y) // sprite hited;
		{
			b->hit |= 1;
			if (b->n_first == -1)
				b->n_first = i;
			else
				b->n_last = i;
		}
		b = b->next;
	}
}

void ft_show_sprites(t_data *data)
{
	t_lst_sprite *b;

	b = data->sprite_lst;
	while (b)
	{
		printf("x, y: %d, %d, dist: %f, hit: %d, n_f, n_l: %d, %d\n", b->x, b->y, b->dist, b->hit, b->n_first, b->n_last);
		b = b->next;
	}
}

void ft_do_sprites(t_data *data)
{
	int				i;
	float			distx;
	float			disty;
	t_lst_sprite	*b;

	i = 0;
	b = data->sprite_lst;
	while (b)
	{
		if (b->hit == 1)
		{
			distx = (int)data->posx - (int)b->x;
			disty = (int)data->posy - (int)b->y;
			b->dist = sqrt(distx * distx + disty * disty);
			ft_color_sprite(data, b);
		}
		b = b->next;
	}
}

void	ft_lstadd_sprite(t_lst_sprite **alst, t_lst_sprite *new)
{
	if (new == NULL || alst == NULL)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	new->next = *alst;
	*alst = new;
}

t_lst_sprite 	*ft_lst_newsprite(float x, float y)
{
	t_lst_sprite *sprite;

	if (!(sprite = (t_lst_sprite*)malloc(sizeof(t_lst_sprite))))
		return (NULL);
	sprite->dist = 0;
	sprite->hit = 0;
	sprite->x = x;
	sprite->y = y;
	sprite->n_first = -1;
	sprite->n_last = -1;
	/*if ((int)y < y)
		sprite->offset = y - (int)y;
	else if ((int)x < x)
		sprite->offset = x - (int)x;
	else
		sprite->offset = 0;*/
	sprite->next = NULL;
	return (sprite);
}

void 		ft_list_sprites(t_data *data)
{
	int 			i;
	int				j;
	t_lst_sprite	*new;

	i = 0;
	j = 0;
	while (j < data->height)
	{
		while (i < data->width)
		{
			if (data->map[j][i] == 2)
			{
				if (!(new = ft_lst_newsprite(i, j)))
					exit(0);
				ft_lstadd_sprite(&data->sprite_lst, new);
			}
			i++;
		}
		i = 0;
		j++;
	}
}

void 	ft_reset_sprite(t_data *data)
{
 	t_lst_sprite	*b;

	b = data->sprite_lst;
	while (b)
	{
		b->dist = 0;
		b->hit = 0;
		b->n_first = -1;
		b->n_last = -1;
		b = b->next;
	}
}

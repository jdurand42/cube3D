/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/03 19:51:05 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void ft_check_sprite(t_data *data, t_int *coor, int i, int map_value)
{
	float				dist;
	t_lst_sprite		*new;

	if (map_value != 2)
		return ;

	dist = sqrt(((coor->x - data->vec[i].x1) *
	(coor->x - data->vec[i].x1)) +
	((coor->y - data->vec[i].y1) * (coor->y - data->vec[i].y1)));
	if (i < data->R[0] / 2)
		dist *= cos(ft_toradian(30 - data->vec[i].angle_rela));
	else if (i > data->R[0] / 2)
		dist *= cos(ft_toradian(data->vec[i].angle_rela - 30));
	if (!(new = ft_lst_newsprite(dist, coor->x, coor->y))) // with exit function after
		return ;
	ft_lstadd_sprite(&data->vec[i].sprite_lst, new);
	if (i == data->R[0] / 2)
		printf("sprite ici : %f\n", data->vec[i].sprite_lst->dist);
}

void ft_show_sprites(t_data *data)
{
	int i;
	t_lst_sprite *b;

	i = 0;
	while (i < data->R[0])
	{
		if (data->vec[i].sprite_lst)
		{
			printf("sprite in do sprite: %f, %f\n", data->vec[i].sprite_lst->dist, data->vec[i].sprite_lst->offset);
			b = data->vec[i].sprite_lst->next;
			while (b)
			{
				printf("next sprite: %f, %f\n", b->dist, b->offset);
				b = b->next;
			}
		}
		i++;
	}
}

void ft_do_sprites(t_data *data)
{
	int				i;
	t_lst_sprite	*b;

	i = 0;
	while (i < data->R[0])
	{
		b = data->vec[i].sprite_lst;
		while (b)
		{
			ft_do_colum_sprite(data, b, i);
			b = b->next;
		}
		i++;
	}
}

void 	ft_do_colum_sprite(t_data *data, t_lst_sprite *sprite, int i)
{
	unsigned long		j = 0;
	int					hp;
	t_color 			color;
	int					n_pixel;

	color.hp = data->R[1] / sprite->dist;
	color.n_pixel = 1;
	if (color.hp <= data->R[1])
	j = (data->R[1] / 2) - (color.hp / 2);
	else
	{
		j = 0;
		color.n_pixel = (color.hp - data->R[1]) / 2;
	}
	while (j <= (data->R[1] / 2) + (color.hp / 2) && j <  data->R[1])
	{
		ft_get_sprite_ypixel(data, &color, sprite);
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = color.color[0];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = color.color[1];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = color.color[2];
		data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
		j += 1;
		color.n_pixel += 1;
	}
}

void 	ft_get_sprite_ypixel(t_data *data, t_color *sprite_c, t_lst_sprite *sprite)
{
	int	ypixel;
	int offset;
	int sl;

	ypixel = (int)(data->tex[4].h * sprite_c->n_pixel / sprite_c->hp);
	offset = (int)(sprite->offset * data->tex[4].w);
	sl = data->tex[4].sl;
	sprite_c->color[0] = data->tex[4].img[ypixel * sl + (offset * 4)];
	sprite_c->color[1] = data->tex[4].img[ypixel * sl + (offset * 4) + 1];
	sprite_c->color[2] = data->tex[4].img[ypixel * sl + (offset * 4) + 2];
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

t_lst_sprite 	*ft_lst_newsprite(float dist, float x, float y)
{
	t_lst_sprite *sprite;

	if (!(sprite = (t_lst_sprite*)malloc(sizeof(t_lst_sprite))))
		return (NULL);
	sprite->dist = dist;
	if ((int)y < y)
		sprite->offset = y - (int)y;
	else if ((int)x < x)
		sprite->offset = x - (int)x;
	else
		sprite->offset = 0;
	sprite->next = NULL;
	return (sprite);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:55:23 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 17:21:48 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_draw_sprites(t_data *data, int pixel, int sizex, t_sprite *sprite)
{
	int i;
	int xpixel;
	float x_pas;

	i = pixel;
	x_pas = data->tex[4].w / sprite->sizex;
	xpixel = sprite->sizex - sizex;
	while (i < data->R[0] && xpixel < sprite->sizex)
	{
		if (sprite->dist < data->vec[i].dist_towall)
			ft_draw_a_colum_sprite(data, i, sprite->sizey, (int)(xpixel * data->tex[4].h / sprite->sizey));
		i++;
		xpixel += 1;
	}
}

void 	ft_draw_a_colum_sprite(t_data *data, int i, int hp, int xpixel)
{
	int					j;
	int					tab[3];
	int					n_pixel;
	unsigned char		c[3];

	ft_init_draw_sprite(data, &j, &n_pixel, hp);
	tab[0] = hp;
	tab[1] = xpixel;
	tab[2] = n_pixel;
	while (j <= (data->R[1] / 2) + (hp / 2) && j <  data->R[1])
	{
		ft_get_tex_ypixel_sprite(data, tab, c);
		if (!(c[0] == 0 && c[1] == 0 && c[2] == 0))
		{
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = (char)c[0];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = (char)c[1];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = (char)c[2];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
		}
		j++;
		n_pixel += 1;
		tab[2] = n_pixel;
	}
}

void 	ft_init_draw_sprite(t_data *data, int *j, int *n_pixel, int hp)
{
	*n_pixel = 1;
	*j = 0;
	if (hp <= data->R[1])
		*j = (data->R[1] / 2) - (hp / 2);
	else
	{
		*j = 0;
		*n_pixel = (hp - data->R[1]) / 2;
	}
}

void 	ft_get_tex_ypixel_sprite(t_data *data, int *tab, unsigned char *color)
{
	int	ypixel;
	int	n_pixel;
	int	xpixel;
	int	hp;

	n_pixel = tab[2];
	xpixel = tab[1];
	hp = tab[0];
	ypixel = (int)(data->tex[4].h * n_pixel / hp);
	if (ypixel > data->tex[4].h - 1)
		ypixel = data->tex[4].h - 1;
	if (xpixel > data->tex[4].w - 1)
		xpixel = data->tex[4].w - 1;
	color[0] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4)];
	color[1] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4) + 1];
	color[2] = data->tex[4].img[ypixel * data->tex[4].sl + (xpixel * 4) + 2];
}

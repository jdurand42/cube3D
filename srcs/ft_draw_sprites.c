/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:55:23 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/05 17:24:43 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_draw_sprites(t_data *data)
{
	int	tex_x;
	int tex_y;
	int n_sprite;
	int pixel_hit;

	n_sprite = 0;
	while (n_sprite < data->s_max && data->tsprite[n_sprite].hit == 1)
	{
		pixel_hit = data->tsprite[n_sprite].pixel_hit;
		while (data->tsprite[n_sprite].sizex) // for a sprite
		{
			if (data->tsprite[n_sprite].dist < data->vec[pixel_hit].dist_towall) // zbuffer
			{
				tex_x = data->tex[4].w * data->tsprite[n_sprite].offset;
				ft_draw_a_colum_sprite(data, tex_x, pixel_hit, &data->tsprite[n_sprite]);
			}
			pixel_hit += 1;
			data->tsprite[n_sprite].offset -= 60 / (double)data->R[0];
			data->tsprite[n_sprite].sizex -= 1;
		}
		n_sprite += 1;
	}
}

void 	ft_draw_a_colum_sprite(t_data *data, int tex_x, int pixel_hit, t_sprite *sprite)
{
	int j;
	int i;

	j = 0;
	i = 0;
	j = data->R[1] / 2 - sprite->sizey / 2;
	while (j < data->R[1] && j <= data->R[1] / 2 + sprite->sizey / 2)
	{
						//printf("dddd\n");
		data->img[j * data->sl + (data->R[0] - (pixel_hit * 4))] = (char)0;
		data->img[j * data->sl + (data->R[0] - (pixel_hit * 4)) + 1] = (char)0;
		data->img[j * data->sl + (data->R[0] - (pixel_hit * 4)) + 2] = (char)255;
		data->img[j * data->sl + (data->R[0] - (pixel_hit * 4)) + 3] = (char)0;
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:11:46 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:13:57 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void			ft_do_colum(t_data *data)
{
	int		j;
	int		i;
	t_color	color;

	j = 0;
	i = 0;
	while (i < data->R[0])
	{
		ft_init_t_color(data, &color, i, &j);
		while (j <= (data->R[1] / 2) + (color.hp / 2) && j < data->R[1])
		{
			ft_get_tex_ypixel(data, &color);
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] =
				color.color[0];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] =
				color.color[1];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] =
				color.color[2];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
			j += 1;
			color.n_pixel += 1;
		}
		i++;
	}
}

void			ft_init_t_color(t_data *data, t_color *color, int i, int *j)
{
	color->hp = ft_get_dist_info(data, i);
	color->tex_x = ft_get_tex_xpixel(data, color, i);
	color->n_pixel = 1;
	if (color->hp <= data->R[1])
		*j = (data->R[1] / 2) - (color->hp / 2);
	else
	{
		*j = 0;
		color->n_pixel = (color->hp - data->R[1]) / 2;
	}
}

void			ft_get_tex_ypixel(t_data *data, t_color *color)
{
	int	ypixel;
	int	i;

	i = color->side;
	ypixel = (int)(data->tex[i].h * color->n_pixel / color->hp);
	if (ypixel > data->tex[i].h - 1)
		ypixel = data->tex[i].h - 1;
	if (color->tex_x > data->tex[i].w - 1)
		color->tex_x = data->tex[i].w - 1;
	color->color[0] =
		data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4)];
	color->color[1] =
		data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4) + 1];
	color->color[2] =
		data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4) + 2];
}

unsigned int	ft_get_tex_xpixel(t_data *data, t_color *color, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
			color->side = 2;
		else
			color->side = 0;
		return ((int)(data->tex[color->side].w * data->vec[i].id_wally));
	}
	else
	{
		if (data->vec[i].rotx < 0)
			color->side = 1;
		else
			color->side = 3;
		return ((int)(data->tex[color->side].w * data->vec[i].id_wallx));
	}
}
/*
** wall_type 0 > x > E ou W
** wall_type 1 > y > N ou S
** roty	> 0    >   > S ou E Ou W
** roty < 0    >   > N ou E ou W
** rotx > 0    >   > W ou N ou S
** rotx < 0    >   > E ou N ou S
** if wall_type 1
**	-> roty > 0 -> S
**  -> roty < 0 -> N
** if wall_type 0
**	-> rotx > 0 -> W
**  -> rotx < 0 -> E
*/

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:11:46 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 19:11:45 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int	ft_setup_tex(t_data *data)
{
	if (!(data->tex[0].img_p = mlx_xpm_file_to_image(data->mlx_p, data->NO,
		&data->tex[0].w, &data->tex[0].h)))
		return (0);
	if (!(data->tex[1].img_p = mlx_xpm_file_to_image(data->mlx_p, data->ES,
		&data->tex[1].w, &data->tex[1].h)))
		return (0);
	if (!(data->tex[2].img_p = mlx_xpm_file_to_image(data->mlx_p, data->SO,
		&data->tex[2].w, &data->tex[2].h)))
		return (0);
	if (!(data->tex[3].img_p = mlx_xpm_file_to_image(data->mlx_p, data->WE,
		&data->tex[3].w, &data->tex[3].h)))
		return (0);
	if (!(data->tex[4].img_p = mlx_xpm_file_to_image(data->mlx_p, data->S,
		&data->tex[4].w, &data->tex[4].h)))
		return (0);
	ft_get_info_tex(data->tex);
	return (1);
}

void 	ft_get_info_tex(t_tex *tex)
{
	tex[0].img = mlx_get_data_addr(tex[0].img_p, &tex[0].bpp, &tex[0].sl, &tex[0].endian);
	tex[1].img = mlx_get_data_addr(tex[1].img_p, &tex[1].bpp, &tex[1].sl, &tex[1].endian);
	tex[2].img = mlx_get_data_addr(tex[2].img_p, &tex[2].bpp, &tex[2].sl, &tex[2].endian);
	tex[3].img = mlx_get_data_addr(tex[3].img_p, &tex[3].bpp, &tex[3].sl, &tex[3].endian);
	tex[4].img = mlx_get_data_addr(tex[4].img_p, &tex[4].bpp, &tex[4].sl, &tex[4].endian);
}

void 	ft_do_colum(t_data *data)
{
	unsigned long		j = 0;
	int		hp;
	int		i = 0;
	t_color 			color;

	while (i < data->R[0])
	{
		hp = ft_get_dist_info(data, i);
		color.tex_x = ft_get_tex_xpixel(data, &color, i);
		color.hp = hp;
		color.n_pixel = 1;
		if (hp <= data->R[1])
			j = (data->R[1] / 2) - (hp / 2);
		else
		{
			j = 0;
			color.n_pixel = (color.hp - data->R[1]) / 2;
		}
		while (j <= (data->R[1] / 2) + (hp / 2) && j <  data->R[1])
		{
			ft_get_tex_ypixel(data, &color);
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 0] = color.color[0];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 1] = color.color[1];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 2] = color.color[2];
			data->img[j * data->sl + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
			j += 1;
			color.n_pixel += 1;
		}
		i++;
	}
}

int 	ft_get_dist_info(t_data *data, int i)
{
	float 	distance;
	double		hp;

	if (i < data->R[0])
		distance = data->vec[i].dist_towall * cos(ft_toradian(30 - data->vec[i].angle_rela));
	else if (i > data->R[0])
		distance = data->vec[i].dist_towall * cos(ft_toradian(data->vec[i].angle_rela - 30));
	hp = data->R[1] / (double)distance;
	return ((int)(data->R[1] / distance));
}

void 	ft_get_tex_ypixel(t_data *data, t_color *color)
{
	int	ypixel;
	int i;

	i = color->side;
	ypixel = (int)(data->tex[i].h * color->n_pixel / color->hp);
	if (ypixel > data->tex[i].h - 1)
		ypixel = data->tex[i].h - 1;
	if (color->tex_x > data->tex[i].w - 1)
		color->tex_x = data->tex[i].w - 1;
	color->color[0] = data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4)];
	color->color[1] = data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4) + 1];
	color->color[2] = data->tex[i].img[ypixel * data->tex[i].sl + (color->tex_x * 4) + 2];
}

unsigned int 	ft_get_tex_xpixel(t_data *data, t_color *color, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
		{
			color->side = 2;
			return ((int)(data->tex[2].w * data->vec[i].id_wally)); //sud
		}
		else
		{
			color->side = 0;
			return ((int)(data->tex[0].w * data->vec[i].id_wally)); // nord
		}
	}
	else
	{
		if (data->vec[i].rotx < 0)
		{
			color->side = 1;
			return ((int)(data->tex[1].w * data->vec[i].id_wallx)); // E
		}
		else
		{
			color->side = 3;
			return ((int)(data->tex[3].w * data->vec[i].id_wallx)); // W
		}
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
**
*/

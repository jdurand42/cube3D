/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 15:11:46 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/02 17:13:21 by jdurand          ###   ########.fr       */
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
	//if sprites
	ft_get_info_tex(data->tex);
	return (1);
}

void 	ft_get_info_tex(t_tex *tex)
{
	tex[0].img = mlx_get_data_addr(tex[0].img_p, &tex[0].bpp, &tex[0].sl, &tex[0].endian);
	tex[1].img = mlx_get_data_addr(tex[1].img_p, &tex[1].bpp, &tex[1].sl, &tex[1].endian);
	tex[2].img = mlx_get_data_addr(tex[2].img_p, &tex[2].bpp, &tex[2].sl, &tex[2].endian);
	tex[3].img = mlx_get_data_addr(tex[3].img_p, &tex[3].bpp, &tex[3].sl, &tex[3].endian);
}

void 	ft_do_colum(t_data *data)
{
	unsigned long int		j = 0;
	int		hp;
	int		i = 0;
	unsigned int 			color;
	int 					n_pixel = 1;

	while (i < data->R[0])
	{
		hp = ft_get_dist_info(data, i);
		color = ft_choose_color(data, i);
		j = (data->R[1] / 2 * data->sl) - (hp / 2 * data->sl);
			while (j >= (data->R[1] / 2 * data->sl) - (hp / 2 * data->sl) && j < (data->R[1] / 2 * data->sl) + (hp / 2 * data->sl))
			{
				data->img[j + (data->R[0] - 1 - i) * 4 + 0] = (char)(color >> 0);
				data->img[j + (data->R[0] - 1 - i) * 4 + 1] = (char)(color >> 8);
				data->img[j + (data->R[0] - 1 - i) * 4 + 2] = (char)(color >> 16);
				data->img[j + (data->R[0] - 1 - i) * 4 + 3] = (char)0;
				j += data->sl;
				n_pixel++;
			}
		i++;
		n_pixel = 1;
	}
}

int 	ft_get_dist_info(t_data *data, int i)
{
	float distance;

	if (i < data->R[0])
		distance = data->vec[i].dist_towall * cos(ft_toradian(30 - data->vec[i].angle_rela));
	else if (i > data->R[0])
		distance = data->vec[i].dist_towall * cos(ft_toradian(data->vec[i].angle_rela - 30));
	if (distance < 1)
		distance = 1;
	return (data->R[1] / distance);
}
/*
unsigned int 	ft_choose_tex_pixel(t_data *data, int i, int hp)
{
	int	tex_w;
	unsigned int color;

	tex_x = ft_get_tex_pixel(data, i);
	color = ft_regle_de_3(data, i, hp, tex_x);

}

unsigned int ft_regle_de_3(t_data *data, int i, int hp, int tex_w, int n_pixel)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
	 	{

		}//sud
		else
			return ((int)(data->tex[0].w * data->vec[i].id_wally)); // nord
	}
}

unsigned int 	ft_get_tex_xpixel(t_data *data, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
			return ((int)(data->tex[2].w * data->vec[i].id_wally)); //sud
		else
			return ((int)(data->tex[0].w * data->vec[i].id_wally)); // nord
	}
	else
	{
		if (data->vec[i].rotx < 0)
			return ((int)(data->tex[1].w * data->vec[i].wallx)); // E
		else
			return ((int)(data->tex[3].w * data->vec[i].wally)); // W
	}
}

unsigned int 	ft_get_tex_pixel(t_data *data, t_tex *tex, int i)
{

}å
*/
unsigned int 	ft_choose_color(t_data *data, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
			return (ft_rgb(255, 0, 0)); //sud
		else
			return (ft_rgb(0, 255, 0)); // nord
	}
	else
	{
		if (data->vec[i].rotx < 0)
			return (ft_rgb(0, 0, 255)); // E
		else
			return (ft_rgb(0, 0, 0)); // W
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

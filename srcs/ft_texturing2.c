/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texturing2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 16:30:24 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/11 21:14:29 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

int		ft_setup_tex(t_data *data)
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

void	ft_get_info_tex(t_tex *tex)
{
	tex[0].img = mlx_get_data_addr(tex[0].img_p, &tex[0].bpp, &tex[0].sl,
		&tex[0].endian);
	tex[1].img = mlx_get_data_addr(tex[1].img_p, &tex[1].bpp, &tex[1].sl,
		&tex[1].endian);
	tex[2].img = mlx_get_data_addr(tex[2].img_p, &tex[2].bpp, &tex[2].sl,
		&tex[2].endian);
	tex[3].img = mlx_get_data_addr(tex[3].img_p, &tex[3].bpp, &tex[3].sl,
		&tex[3].endian);
	tex[4].img = mlx_get_data_addr(tex[4].img_p, &tex[4].bpp, &tex[4].sl,
		&tex[4].endian);
}

int		ft_get_dist_info(t_data *data, int i)
{
	float	distance;

	if (i < data->R[0])
		distance = data->vec[i].dist_towall *
			cos(ft_toradian(30 - data->vec[i].angle_rela));
	else if (i > data->R[0])
		distance = data->vec[i].dist_towall *
			cos(ft_toradian(data->vec[i].angle_rela - 30));
	return ((int)(data->R[1] / distance));
}

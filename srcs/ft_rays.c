/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/12 14:27:39 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void	ft_setup_rays(t_data *data, int **map)
{
	int		i;
	float	pas;

	pas = 60 / (float)data->R[0];
	i = 0;
	data->vec = NULL;
	data->dda = NULL;
	if (!(data->vec = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return (ft_exit_all(data));
	if (!(data->dda = (t_dda*)malloc(data->R[0] * sizeof(t_dda))))
		return (ft_exit_all(data));
	while (i < data->R[0])
	{
		data->vec[i].angle_rela = (float)i * pas;
		i++;
	}
}

void	do_rays(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->R[0])
	{
		ft_setray(data, i);
		while (data->vec[i].wall_type == -1)
		{
			ft_dda(data, i);
			if (data->vec[i].angle == 0)
				ft_sparadrap(data, i);
		}
		i++;
	}
	ft_do_colum(data);
	if (data->tsprite)
	{
		ft_do_dist_sprite(data);
		ft_check_if_visible(data);
	}
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void	ft_setray(t_data *data, int i)
{
	float	pas;

	pas = 60 / (float)data->R[0];
	data->vec[i].x1 = data->posx;
	data->vec[i].y1 = data->posy;
	data->vec[i].angle = data->cam.angle - (60 / 2) + ((float)i * pas);
	if (data->vec[i].angle > 359)
		data->vec[i].angle = data->vec[i].angle - 359;
	else if (data->vec[i].angle < 0)
		data->vec[i].angle = 360 + data->vec[i].angle;
	data->vec[i].rotx = cos(ft_toradian(data->vec[i].angle));
	data->vec[i].roty = sin(ft_toradian(data->vec[i].angle));
	data->vec[i].wall_type = -1;
	data->vec[i].tan_theta = 0;
}

void	ft_sparadrap(t_data *data, int i)
{
	data->vec[i].wall_type = 0;
	if (i > 0)
		data->vec[i].dist_towall = data->vec[i - 1].dist_towall;
	else
		data->vec[i].dist_towall = data->vec[i + 1].dist_towall;
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

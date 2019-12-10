/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:08:39 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/10 16:39:33 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"

void 	ft_setup_rays(t_data *data, int **map)
{
	int 	i;
	float pas = 60 / (double)data->R[0];

	i = 0;
	data->vec = NULL;
	data->dda = NULL;
	if (!(data->vec = (t_vector*)malloc(data->R[0] * sizeof(t_vector))))
		return ;
	if (!(data->dda = (t_dda*)malloc(data->R[0] * sizeof(t_dda))))
		return ;
	data->cam.angle = ft_get_angle(data, map);
	while (i < data->R[0])
	{
		data->vec[i].angle_rela = (float)i * pas;
		i++;
	}
}

void 	do_rays(t_data *data)
{
	int i = 0;

	while (i < data->R[0])
	{
		ft_setray(data, i);
		while (data->vec[i].wall_type == -1)
		{
			ft_dda(data, i);
			if (i == 0 || i == data->R[0] - 1)
			{
				printf("%f, %f\n", data->posx, data->posy);
				printf("i: %d cam: %f, angle: %f\n", i, data->cam.angle, data->vec[i].angle);
			}
		}
		i++;
	}
	ft_do_colum(data);
	if (data->tsprite)
	{
		ft_do_dist_sprite(data);
		ft_check_if_visible(data);
	}
	//printf(GREEN "---------------\n" RESET);
	mlx_put_image_to_window(data->mlx_p, data->mlx_wd, data->mlx_img, 0, 0);
}

void 	ft_setray(t_data *data, int i)
{
	float pas;

	pas = 60 / (float)data->R[0];
	data->vec[i].x1 = data->posx;
	data->vec[i].y1 = data->posy;
	data->vec[i].angle = data->cam.angle - (60 / 2) + ((float)i * pas);
	if (data->vec[i].angle > 359)
		data->vec[i].angle = data->vec[i].angle - 359;
	else if (data->vec[i].angle < 0)           /// a voir probablement un bug ici
		data->vec[i].angle = 360 + data->vec[i].angle;
	//printf("vec %d: angle: %lf\n", i, data->vec[i].angle);
	data->vec[i].rotx = cos(ft_toradian(data->vec[i].angle));
	data->vec[i].roty = sin(ft_toradian(data->vec[i].angle));
	data->vec[i].wall_type = -1;
	// i = data->vec[i].angle / pas - (60 / 2) + data->cam.angle
//	if (i == data->R[0] / 2) //|| i == 0 || i == data->R[0] - 1)
	//	printf(GREEN "ray %d: x1: %lf, y1: %lf\nangle : %lf\n, rotx : %lf, roty: %lf\n"
//		RESET, i, data->vec[i].x1, data->vec[i].y1, data->vec[i].angle,
//		data->vec[i].rotx, data->vec[i].roty);
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
/*
unsigned int 	ft_choose_color(t_data *data, int i)
{
	if (data->vec[i].wall_type == 1)
	{
		if (data->vec[i].roty > 0)
			return (ft_rgb(128, 208, 208));
		else
			return (ft_rgb(173, 216, 230));
	}
	else
	{
		if (data->vec[i].rotx < 0)
			return (ft_rgb(187, 210, 225));
		else
			return (ft_rgb(0, 128, 128));
	}
}
*/

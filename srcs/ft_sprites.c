/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/05 20:58:20 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 		ft_check_if_hit(t_data *data) // marchera pas dans le dda
{
	int s = 0;
	int i = 0;
	float x, y;
	float theta;
	float dist_r;
	float delta;
	float tan_theta;

	while (s < data->s_max)
	{
		while (i < data->R[0])
		{
				theta = data->vec[i].angle_rela;
				if (theta > 30)
				 	theta = theta - 30;
				else if (theta < 30)
					theta = 30 - theta;
				tan_theta = tan(ft_toradian(theta));
				delta = data->tsprite[s].dist * tan_theta;
				dist_r = sqrt(delta * delta + data->tsprite[s].dist * data->tsprite[s].dist);
				printf("%f\n", dist_r);
				x = data->posx + (dist_r * data->vec[i].rotx);
				y = data->posy - (dist_r * data->vec[i].roty);
		//	if ((int)y == (int)data->tsprite[s].y && (int)x == (int)data->tsprite[s].x)
				printf(GREEN "sp n : %d, RAYON: %i, x, y hit: %f, %f\n" RESET, s, i, x, y);
			i++;
		}
		printf("--------------------\n");
		i = 0;
		s++;
	}
}

void 	ft_do_dist_sprite(t_data *data)
{
	int		i;
	float	distx;
	float	disty;

	i = 0;
	while (i < data->s_max)
	{
		distx = data->posx - data->tsprite[i].x;
		disty = data->posy - data->tsprite[i].y;
		data->tsprite[i].distx = distx;
		data->tsprite[i].disty = disty;
		data->tsprite[i].dist = sqrt((distx * distx) + (disty * disty));
		data->tsprite[i].sizey = (int)(data->R[1] / data->tsprite[i].dist);
		data->tsprite[i].sizex = (int)(data->tsprite[i].sizey / 2);
		i++;
	}
	printf(GREEN "--Presort--\n" RESET);
	//ft_show_tsprite(data->tsprite, data->s_max);
	ft_do_sort_sprite(data);
	printf(GREEN "--Postsort--\n" RESET);
	ft_show_tsprite(data->tsprite, data->s_max);
}

void 	ft_show_tsprite(t_sprite *tsprite, int s_max)
{
	int i;

	i = 0;
	while (i < s_max)
	{
		printf("i : %d x, y: %d, %d, pix %d, hit: %d, dist: %f, offset: %f\nsizexy: %d, %d\n", i,
		tsprite[i].x, tsprite[i].y, tsprite[i].pixel_hit, tsprite[i].hit, tsprite[i].dist,
		tsprite[i].offset, tsprite[i].sizex, tsprite[i].sizey);
		i++;
	}
}

void		ft_do_tsprite(t_data *data)
{
	int x;
	int y;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	if (!(data->tsprite = (t_sprite*)malloc(data->s_max * sizeof(t_sprite))))
		exit(0);
	while (y < data->height)
	{
		while (x < data->width)
		{
			if (data->map[y][x] == 2)
			{
				printf("%d, %d\n", x, y);
				data->tsprite[i].x = x;
				data->tsprite[i].y = y;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
	ft_reset_tsprite(data->tsprite, data->s_max);
}

void 	ft_reset_tsprite(t_sprite *tsprite, int s_max)
{
	int i = 0;

	while (i < s_max)
	{
		tsprite[i].pixel_hit = -1;
		tsprite[i].hit = 0;
		tsprite[i].offset = -1;
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		tsprite[i].dist = -1;
		tsprite[i].sizex = 0;
		tsprite[i].sizey = 0;
		i++;
	}
}

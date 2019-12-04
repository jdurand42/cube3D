/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdurand <jdurand@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:45:29 by jdurand           #+#    #+#             */
/*   Updated: 2019/12/04 20:44:00 by jdurand          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3D.h"


void 		ft_check_if_hit(t_data *data, int i, int map, t_int *coor)
{
	int s;

	s = 0;
	if (!(map == 2))
		return ;
	while (s < data->s_max)
	{
		if (data->tsprite[s].x == (int)coor->x && data->tsprite[s].y == (int)coor->y)
		{
			data->tsprite[s].hit |= 1;
			if (data->tsprite[s].pixel_hit == -1)
			{
				data->tsprite[s].pixel_hit = i;
				if ((int)coor->x == coor->x)
					data->tsprite[s].offset = coor->x - (int)coor->x;
				else
				data->tsprite[s].offset = coor->y - (int)coor->y;
			}
		}
		s++;
	}
}

void 	ft_show_tsprite(t_sprite *tsprite, int s_max)
{
	int i;

	i = 0;
	while (i < s_max)
	{
		printf("i : %d x, y: %d, %d, pix %d, hit: %d, dist: %f, offset: %f\n", i,
		tsprite[i].x, tsprite[i].y, tsprite[i].pixel_hit, tsprite[i].hit, tsprite[i].dist,
		tsprite[i].offset);
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
				data->tsprite[i].pixel_hit = -1;
				data->tsprite[i].hit = 0;
				data->tsprite[i].offset = -1;
				i++;
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void 	ft_reset_tsprite(t_sprite *tsprite, int s_max)
{
	int i = 0;

	while (i < s_max)
	{
		tsprite[i].pixel_hit = -1;
		tsprite[i].hit = 0;
		tsprite[i].offset = -1;
		i++;
	}
}
